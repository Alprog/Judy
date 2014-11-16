
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(void* object, ITypeMeta* const typeMeta)
{
    if (typeMeta == &TypeMeta<int>::instance)
    {
        lua_pushnumber(L, *(int*)object);
    }
    else if (typeMeta == &TypeMeta<std::string>::instance)
    {
        lua_pushstring(L, (*(std::string*)object).c_str());
    }
    else if (typeMeta == &TypeMeta<char*>::instance)
    {
        lua_pushstring(L, *(char**)object);
    }
    else
    {
        lua_newtable(L);

        for (auto fieldMeta : typeMeta->fields)
        {
            void* value = fieldMeta->get(object);
            Serialize(value, fieldMeta->GetType());
            lua_setfield(L, -2, fieldMeta->name);
        }
    }
}

Variant Serializer::Deserialize(ITypeMeta* const typeMeta)
{
    if (typeMeta == &TypeMeta<int>::instance)
    {
        return lua_tointeger(L, -1);
    }
    else if (typeMeta == &TypeMeta<std::string>::instance)
    {
        return std::string( lua_tostring(L, -1) );
    }
    else if (typeMeta == &TypeMeta<char*>::instance)
    {
        return lua_tostring(L, -1);
    }
    else
    {
        Variant object = typeMeta->DefaultConstructor();

        for (auto fieldMeta : typeMeta->fields)
        {
            lua_getfield(L, -1, fieldMeta->name);

            Variant value = Deserialize(fieldMeta->GetType());

            fieldMeta->set(object, value);
            lua_pop(L, 1);
        }

        return object;
    }
}
