
#pragma once

#include <string>

class Meta;
class lua_State;
class IClassMeta;
class Any;
class ITypeMeta;
class IFunctionMeta;

using luaClosure = int(*)(lua_State*);

class LuaBinder
{
public:
    LuaBinder(lua_State* L);
    void Bind(Meta* meta);

private:
    void BindClass(IClassMeta* classMeta);
    void BindHelper(IFunctionMeta* function, std::string name, luaClosure closure);

    lua_State* L;
};
