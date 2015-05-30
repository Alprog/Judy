
#pragma once

class Meta;
class lua_State;

class LuaBinder
{
public:
    LuaBinder(lua_State* L);
    void Bind(Meta* meta);

private:
    lua_State* L;
};
