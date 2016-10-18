
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
    void Bind(Meta* meta);

private:
    void Init();

    void BindClass(IClassMeta* classMeta);
    void BindHelper(std::string name, luaCFunction closure, void* upvalue);

    lua_State* L;
};
