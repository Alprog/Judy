
#pragma once

class Meta;
class lua_State;
class IClassMeta;

class LuaBinder
{
public:
    LuaBinder(lua_State* L);
    void Bind(Meta* meta);

private:
    void BindClass(IClassMeta* classMeta);

    lua_State* L;
};
