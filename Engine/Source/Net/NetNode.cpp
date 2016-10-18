
#include "NetNode.h"
#include <luainc.h>

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
    socket = Socket::create();
    socket->setBlockingMode(false);
}

NetNode::~NetNode()
{
    state = State::Disconnected;
    if (workThread != nullptr)
    {
        if (workThread->joinable())
        {
            workThread->join();
        }
        delete workThread;
    }

    delete socket;
    delete serializer;
}

NetNode::State NetNode::getState() const
{
    return state;
}

bool NetNode::isConnected() const
{
    return state == State::Connected;
}

void NetNode::start(int port)
{
    this->port = port;
    socket->listen(port);
    this->state = State::ClientWaiting;
    startWork();
}

void NetNode::connect(std::string host, int port)
{
    this->host = host;
    this->port = port;
    this->state = State::Connecting;
    startWork();
}

void NetNode::send(Any any)
{
    mutex.lock();
    auto text = serializer->serialize(any);
    output.append(text);
    output += '\0';
    mutex.unlock();
}

void NetNode::startWork()
{
    workThread = new std::thread(&NetNode::work, this);
}

void NetNode::work()
{
    while (state != State::Disconnected)
    {
        if (state == State::ClientWaiting)
        {
            clientWaitWork();
        }
        else if (state == State::Connecting)
        {
            connectWork();
        }
        else if (state == State::Connected)
        {
            if (customWorkCallback != nullptr)
            {
                customWorkCallback();
            }
            sendWork();
            receiveWork();
            processMessages();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void NetNode::clientWaitWork()
{
    auto clientSocket = socket->accept();
    if (clientSocket != nullptr)
    {
        clientSocket->setBlockingMode(false);
        delete socket;
        socket = clientSocket;
        state = State::Connected;
    }
}

void NetNode::connectWork()
{
    if (socket->connect(host, port))
    {
        state = State::Connected;
    }
    else
    {
        auto error = socket->getLastError();
        if (error == Socket::Error::AlreadyConnected)
        {
            state = State::Connected;
        }
        else if (error == Socket::Error::InvalidArgument)
        {
            delete socket;
            socket = Socket::create();
            socket->setBlockingMode(false);
        }
    }
}

bool NetNode::hasOutput() const
{
    return output.size() > 0;
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
            auto count = socket->send(buffer + totalSend, length - totalSend);
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

void NetNode::receiveWork()
{
    char buffer[MAX];
    int count;
    do
    {
        count = socket->receive(buffer, MAX);
        if (count == 0)
        {
            state = State::Disconnected;
        }
        else if (count < 0)
        {
            auto error = socket->getLastError();
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

void NetNode::processMessages()
{
    while (input.size())
    {
        auto index = input.find('\0');
        if (index >= 0)
        {
            auto messageText = input.substr(0, index);
            mutex.lock();
            auto message = serializer->deserialize(messageText);
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
