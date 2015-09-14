
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
    , socket{nullptr}
    , messageCallback{nullptr}
    , customWorkCallback{nullptr}
{
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    luaL_dofile(L, "Serializer.lua");
    serializer = new Serializer(L);

    socket = Socket::Create();
    socket->SetBlockingMode(false);
}

NetNode::~NetNode()
{
    state = State::Disconnected;
    if (workThread != nullptr)
    {
        workThread->detach();
        delete workThread;
    }

    delete serializer;
    lua_close(L);
    L = nullptr;
}

NetNode::State NetNode::GetState() const
{
    return state;
}

bool NetNode::IsConnnected() const
{
    return state == State::Connected;
}

void NetNode::Start(int port)
{
    this->port = port;
    socket->Listen(port);
    this->state = State::ClientWaiting;
    StartWork();
}

void NetNode::Connect(std::string host, int port)
{
    this->host = host;
    this->port = port;
    this->state = State::Connecting;
    StartWork();
}

void NetNode::Send(Any any)
{
    auto text = serializer->Serialize(any);
    output.append(text);
    output += '\0';
}

void NetNode::StartWork()
{
    workThread = new std::thread(&NetNode::Work, this);
}

void NetNode::Work()
{
    while (state != State::Disconnected)
    {
        if (state == State::ClientWaiting)
        {
            ClientWaitWork();
        }
        else if (state == State::Connecting)
        {
            ConnectWork();
        }
        else if (state == State::Connected)
        {
            if (customWorkCallback != nullptr)
            {
                customWorkCallback();
            }
            SendWork();
            ReceiveWork();
            ProcessMessages();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void NetNode::ClientWaitWork()
{
    auto clientSocket = socket->Accept();
    if (clientSocket != nullptr)
    {
        clientSocket->SetBlockingMode(false);
        delete socket;
        socket = clientSocket;
        state = State::Connected;
    }
}

void NetNode::ConnectWork()
{
    if (socket->Connect(host, port))
    {
        state = State::Connected;
    }
    else
    {
        auto error = socket->GetLastError();
        if (error == Socket::Error::AlreadyConnected)
        {
            state = State::Connected;
        }
    }
}

void NetNode::SendWork()
{
    auto length = output.size();
    if (length > 0)
    {
        auto buffer = output.c_str();
        int totalSend = 0;
        while (totalSend < length)
        {
            auto count = socket->Send(buffer + totalSend, length - totalSend);
            if (count < 0)
            {
                break;
            }
            totalSend += count;
        }
        output.erase(0, totalSend);
    }
}

void NetNode::ReceiveWork()
{
    char buffer[MAX];
    int count;
    do
    {
        count = socket->Receive(buffer, MAX);
        if (count < 0)
        {
            auto error = socket->GetLastError();
            if (error != Socket::Error::WouldBlock)
            {
                state = State::Disconnected;
            }
        }
        else if (count > 0)
        {
            input.append(buffer, count);
        }
    }
    while (count == MAX);
}

void NetNode::ProcessMessages()
{
    while (input.size())
    {
        auto index = input.find('\0');
        if (index >= 0)
        {
            auto messageText = input.substr(0, index);
            auto message = serializer->Deserialize(messageText);
            if (messageCallback != nullptr)
            {
                messageCallback(message);
            }

            input.erase(0, index + 1);
        }
        else
        {
            break;
        }
    }
}
