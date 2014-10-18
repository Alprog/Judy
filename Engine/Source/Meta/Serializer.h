
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "Variant.h"

class Serializer
{
public:
    lua_State* L;

    Serializer(lua_State* L)
    {
        this->L = L;
    }

    template <typename Type>
    void Serialize(Type object)
    {
        lua_createtable(L, 0, 0);
        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        for (auto fieldMeta : typeMeta->fields)
        {
            void* value = fieldMeta->get(&object);
            fieldMeta->Serialize(this, value);
            lua_setfield(L, -2, fieldMeta->name);
        }
    }

    template <typename Type>
    Type Deserialize()
    {
        Type type;

        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        for (auto fieldMeta : typeMeta->fields)
        {
            lua_getfield(L, -1, fieldMeta->name);
            Variant value = fieldMeta->Deserialize(this);
            fieldMeta->set(&type, value);
            lua_pop(L, 1);
        }

        return type;
    }

    //-------------------- SerializeField:

    template <typename Type>
    void SerializeField(void* value)
    {
        Serialize(*(Type*)value);
    }

    template <>
    void SerializeField<int>(void* value)
    {
        lua_pushnumber(L, *(int*)value);
    }

    template <>
    void SerializeField<char*>(void* value)
    {
        lua_pushstring(L, *(char**)value);
    }

    //-------------------- DeserializeField:

    template <typename Type>
    Variant DeserializeField()
    {
        return Deserialize<Type>();
    }

    template <>
    Variant DeserializeField<int>()
    {
        return lua_tointeger(L, -1);
    }

    template <>
    Variant DeserializeField<char*>()
    {
        return lua_tolstring(L, -1, nullptr);
    }
};
