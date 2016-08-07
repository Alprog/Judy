
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
    friend void hook(lua_State *L, lua_Debug *ar);

private:
    LuaMachine();
    ~LuaMachine();

public:
    bool IsStarted() const;
    bool IsBreaked() const;

    void Do(std::string scriptName, bool debug = false);
    void Pause();
    void Continue();
    void StepInto();
    void StepOver();
    void StepOut();
    void Stop();

    void ReleaseUserdata(void* userdata);
    void RetainUserdata(void* userdata);

private:
    void Hook(lua_Debug *ar);
    void Break(lua_Debug *ar);
    CallInfo GetCallInfo(lua_Debug *ar);
    void SuspendExecution();

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
    bool isStarted;
    int level;
    int breakRequiredLevel;
};
