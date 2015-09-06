
#pragma once

#include <string>
#include "Singleton.h"
#include <thread>
#include <atomic>

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

   void EnableDebug();
   void Start(std::string scriptName);
   void Continue();
   void Stop();

private:
   void Hook(lua_State *L, lua_Debug *ar);

public:
    Breakpoints Breakpoints;

private:
   lua_State* L;
   bool isStarted;
   std::atomic_bool	suspended;
};
