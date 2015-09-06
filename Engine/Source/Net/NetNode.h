
#pragma once

#include "Socket.h"
#include "Meta/Any.h"
#include "Meta/Serializer.h"
#include <thread>
#include <atomic>

class NetNode
{
private:
    enum class State
    {
        Disconnected,
        ClientWaiting,
        Connecting,
        Connected
    };

public:
    NetNode();
    ~NetNode();

    bool IsConnnected() const;

    void Start(int port);
    void Connect(std::string host, int port);

    void Send(Any& any);

public:
    State GetState() const;

    void StartWork();
    void Work();

    void ClientWaitWork();
    void ConnectWork();
    void SendWork();
    void ReceiveWork();
    void ProcessMessages();

    lua_State* L;
    Serializer* serializer;
    Socket* socket;
    std::thread* workThread;

    std::atomic<State> state;
    int port;
    std::string host;

    std::string output;
    std::string input;
};
