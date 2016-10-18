
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

    bool isConnected() const;
    bool hasOutput() const;

    void start(int port);
    void connect(std::string host, int port);
    void send(Any any);

    State getState() const;

private:
    void startWork();
    void work();

    void clientWaitWork();
    void connectWork();
    void sendWork();
    void receiveWork();
    void processMessages();

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
