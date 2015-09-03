
#include "NetNode.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

const int MAX = 1024;

NetNode::NetNode()
    : state{State::Disconnected}
    , port{0}
    , workThread{nullptr}
{
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    luaL_dofile(L, "Serializer.lua");
    serializer = new Serializer(L);

    socket.SetBlockingMode(false);
}

NetNode::~NetNode()
{
    state = State::Disconnected;
    if (workThread != nullptr)
    {
        workThread->join();
        delete workThread;
    }

    delete serializer;
    lua_close(L);
    L = nullptr;
}

NetNode::State NetNode::getState() const
{
    return state;
}

bool NetNode::isConnnected() const
{
    return state == State::Connected;
}

void NetNode::listen(int port)
{
    this->port = port;
    socket.Listen(port);
    this->state = State::Listening;
    startWork();
}

void NetNode::connect(std::string host, int port)
{
    this->host = host;
    this->port = port;
    this->state = State::Connecting;
    startWork();
}

void NetNode::send(Any& any)
{
    lua_getglobal(L, "TableToString");
    serializer->Serialize(any);
    lua_pcall(L, 1, 1, 0);
    std::string text = lua_tostring(L, -1);
    output.append(text);
    output.append("\0");
}

void NetNode::startWork()
{
    workThread = new std::thread(&NetNode::work, this);
}

void NetNode::work()
{
    while (state != State::Disconnected)
    {
        if (state == State::Listening)
        {
            if (socket.Accept())
            {
                state = State::Connected;
            }
        }
        else if (state == State::Connecting)
        {
            if (socket.Connect(host, port))
            {
                state = State::Connected;
            }
        }
        else if (state == State::Connected)
        {
            sendWork();
            receiveWork();
            processMessages();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void NetNode::sendWork()
{
    auto length = output.size();
    if (length > 0)
    {
        auto buffer = output.c_str();
        int totalSend = 0;
        while (totalSend < length)
        {
            auto count = socket.Send(buffer + totalSend, length - totalSend);

            printf("send %i %i \n", count, length);
            fflush(stdout);

            if (count < 0)
            {
                break;
            }
            totalSend += count;
        }
        output.erase(0, totalSend);
    }
}

void NetNode::receiveWork()
{
    char buffer[MAX];
    int count;
    do
    {
        count = socket.Receive(buffer, MAX);

        printf("read %i \n", count);
        fflush(stdout);

        if (count > 0)
        {
            input.append(buffer, count);
        }
    }
    while (count == MAX);
}

void NetNode::processMessages()
{
    if (input.size())
    {
        auto index = input.find('\0');
        if (index >= 0)
        {
            printf(input.c_str());
            fflush(stdout);
            //input.substr(0, index);
        }
    }
}
