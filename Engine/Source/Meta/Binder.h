
#pragma once

#include <string>

class Meta;
class lua_State;
class IClassMeta;
class IFunctionMeta;

class LuaBinder
{
public:
    LuaBinder(lua_State* L);
    void Bind(Meta* meta);

private:
    void BindClass(IClassMeta* classMeta);
    void BindFunctionHelper(IFunctionMeta* function, std::string name);

    lua_State* L;
};
