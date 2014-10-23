
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(void* object, TypeMeta* typeMeta)
{
    lua_createtable(L, 0, 0);
    for (auto fieldMeta : typeMeta->fields)
    {
        void* value = fieldMeta->get(object);

        TypeMeta* id = fieldMeta->GetType();

        if (id == ClassMeta<int>::Instance())
        {
            lua_pushnumber(L, *(int*)value);
        }
        else if (id == ClassMeta<char*>::Instance())
        {
            lua_pushstring(L, *(char**)value);
        }
        else
        {
            TypeMeta* meta = fieldMeta->GetType();
            Serialize(value, meta);
        }

        lua_setfield(L, -2, fieldMeta->name);
    }
}

Variant Serializer::Deserialize(TypeMeta* typeMeta)
{
    Variant object = typeMeta->Create();

    for (auto fieldMeta : typeMeta->fields)
    {
        lua_getfield(L, -1, fieldMeta->name);

        TypeMeta* meta = fieldMeta->GetType();

        if (meta == ClassMeta<int>::Instance())
        {
            Variant value = lua_tointeger(L, -1);
            fieldMeta->set(object, value);
        }
        else if (meta == ClassMeta<char*>::Instance())
        {
            Variant value = lua_tolstring(L, -1, nullptr);
            fieldMeta->set(object, value);
        }
        else
        {
            Variant value = Deserialize(meta);
            fieldMeta->set(object, value);
        }

        lua_pop(L, 1);
    }

    return object;
}
