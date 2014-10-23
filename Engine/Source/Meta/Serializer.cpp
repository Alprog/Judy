
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(void* object, ITypeMeta* typeMeta)
{
    lua_createtable(L, 0, 0);
    for (auto fieldMeta : typeMeta->fields)
    {
        void* value = fieldMeta->get(object);

        ITypeMeta* id = fieldMeta->GetType();

        if (id == TypeMeta<int>::Instance())
        {
            lua_pushnumber(L, *(int*)value);
        }
        else if (id == TypeMeta<char*>::Instance())
        {
            lua_pushstring(L, *(char**)value);
        }
        else
        {
            ITypeMeta* meta = fieldMeta->GetType();
            Serialize(value, meta);
        }

        lua_setfield(L, -2, fieldMeta->name);
    }
}

Variant Serializer::Deserialize(ITypeMeta* typeMeta)
{
    Variant object = typeMeta->DefaultConstructor();

    for (auto fieldMeta : typeMeta->fields)
    {
        lua_getfield(L, -1, fieldMeta->name);

        ITypeMeta* meta = fieldMeta->GetType();

        if (meta == TypeMeta<int>::Instance())
        {
            Variant value = lua_tointeger(L, -1);
            fieldMeta->set(object, value);
        }
        else if (meta == TypeMeta<char*>::Instance())
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
