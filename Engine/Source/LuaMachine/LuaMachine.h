
#pragma once

#include <string>
#include "Singleton.h"
#include <thread>
#include <atomic>
#include "CallStack.h"
#include "Breakpoints.h"

class lua_State;
class lua_Debug;

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

   void Start(std::string scriptName, bool debug = false);
   void Pause();
   void Continue();
   void StepInto();
   void StepOver();
   void StepOut();
   void Stop();

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

private:
   lua_State* L;
   std::atomic<bool> suspended;
   bool isStarted;
   int level;
   int breakRequiredLevel;
};
