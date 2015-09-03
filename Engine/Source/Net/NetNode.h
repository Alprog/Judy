
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
        Listening,
        Connecting,
        Connected
    };

public:
    NetNode();
    ~NetNode();

    bool isConnnected() const;

    void listen(int port);
    void connect(std::string host, int port);

    void send(Any& any);

private:   
    State getState() const;

    void startWork();
    void work();
    void sendWork();
    void receiveWork();
    void processMessages();

    lua_State* L;
    Serializer* serializer;
    Socket socket;
    std::thread* workThread;

    std::atomic<State> state;
    int port;
    std::string host;

    std::string output;
    std::string input;
};
