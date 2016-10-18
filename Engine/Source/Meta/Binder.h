
#pragma once

#include <string>

class Meta;
struct lua_State;
class IClassMeta;
class Any;
class ITypeMeta;
class IFunctionMeta;

using luaCFunction = auto (*)(lua_State*) -> int;

class LuaBinder
{
public:
    LuaBinder(lua_State* L);
    void bind(Meta* meta);

private:
    void init();

    void bindClass(IClassMeta* classMeta);
    void bindHelper(std::string name, luaCFunction closure, void* upvalue);

    lua_State* L;
};
