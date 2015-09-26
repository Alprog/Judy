
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
    serializer = new Serializer();
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
}

NetNode::State NetNode::GetState() const
{
    return state;
}

bool NetNode::IsConnected() const
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
    mutex.lock();
    auto text = serializer->Serialize(any);
    output.append(text);
    output += '\0';
    mutex.unlock();
}

void NetNode::StartWork()
{
    workThread = new std::thread(&NetNode::Work, this);
}

void NetNode::Work()
{
    while (state != State::Disconnected)
    {
        //int i = (int)(State)state;
        //printf("status: %i\n", i);
        //fflush(stdout);

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

bool NetNode::HasOutput() const
{
    return output.size() > 0;
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
        mutex.lock();
        output.erase(0, totalSend);
        mutex.unlock();
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
            mutex.lock();
            auto message = serializer->Deserialize(messageText);
            mutex.unlock();
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
