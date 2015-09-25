
#pragma once

#include "Socket.h"
#include "Meta/Any.h"
#include "Meta/Serializer.h"
#include "Singleton.h"
#include <thread>
#include <atomic>
#include <functional>
#include <mutex>

class NetNode
{
public:
    enum class State
    {
        Disconnected,
        ClientWaiting,
        Connecting,
        Connected
    };

    NetNode();
    ~NetNode();

    bool IsConnected() const;

    void Start(int port);
    void Connect(std::string host, int port);
    void Send(Any any);

    State GetState() const;

private:
    void StartWork();
    void Work();

    void ClientWaitWork();
    void ConnectWork();
    void SendWork();
    void ReceiveWork();
    void ProcessMessages();

public:
    std::function<void(Any&)> messageCallback;
    std::function<void()> customWorkCallback;

private:
    Serializer* serializer;
    Socket* socket;
    std::thread* workThread;

    std::atomic<State> state;
    int port;
    std::string host;

    std::string output;
    std::string input;
    std::mutex mutex;
};
