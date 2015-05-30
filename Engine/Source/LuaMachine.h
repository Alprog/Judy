
#pragma once

#include <string>
#include "Singleton.h"

class lua_State;

class LuaMachine : public Singleton<LuaMachine>
{
    friend class Singleton<LuaMachine>;

private:
    LuaMachine();
    ~LuaMachine();

public:
   void Start(std::string scriptName);
   void Stop();

private:
   lua_State* L;
};
