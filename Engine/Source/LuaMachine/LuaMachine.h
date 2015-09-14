
#pragma once

#include <string>
#include "Singleton.h"
#include <thread>
#include <atomic>
#include "CallInfo.h"
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
   void Break();
   void Continue();
   void Stop();

private:
   void Hook(lua_State *L, lua_Debug *ar);

public:
    Breakpoints breakpoints;
    std::vector<CallInfo> stack;
    void (*breakCallback)(LuaMachine*);

private:
   lua_State* L;
   bool isStarted;
   std::atomic_bool breakRequired;
   std::atomic_bool	suspended;
};
