
#pragma once

#include <string>
#include "Singleton.h"
#include <thread>
#include <atomic>
#include "CallStack.h"
#include "Breakpoints.h"
#include "Meta/Binder.h"

struct lua_State;
struct lua_Debug;

class LuaMachine : public Singleton<LuaMachine>
{
    friend class Singleton<LuaMachine>;
    friend void hookHelper(lua_State *L, lua_Debug *ar);

private:
    LuaMachine();
    ~LuaMachine();

public:
    bool isStarted() const;
    bool isBreaked() const;

    void execute(std::string scriptName, bool debug = false);
    void pause();
    void resume();
    void stepInto();
    void stepOver();
    void stepOut();
    void stop();

    void releaseUserdata(void* userdata);
    void retainUserdata(void* userdata);

private:
    void hook(lua_Debug *ar);
    void onBreak(lua_Debug *ar);
    CallInfo getCallInfo(lua_Debug *ar);
    void suspendExecution();

public:
    Breakpoints breakpoints;
    CallStack stack;
    std::function<void()> breakCallback;
    std::function<void()> resumeCallback;
    lua_State* getL() const { return L; }

private:
    lua_State* L;
    LuaBinder* binder;
    std::atomic<bool> suspended;
    bool m_isStarted;
    int level;
    int breakRequiredLevel;
};
