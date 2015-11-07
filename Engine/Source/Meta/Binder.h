
#pragma once

#include <string>

class Meta;
class lua_State;
class IClassMeta;
class Any;
class ITypeMeta;
class IFunctionMeta;

using luaCFunction = int(*)(lua_State*);

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
