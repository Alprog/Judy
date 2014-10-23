
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(void* object, ITypeMeta* typeMeta)
{
    lua_createtable(L, 0, 0);
    for (auto IIFieldMeta : typeMeta->fields)
    {
        void* value = IIFieldMeta->get(object);

        ITypeMeta* id = IIFieldMeta->GetType();

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
            ITypeMeta* meta = IIFieldMeta->GetType();
            Serialize(value, meta);
        }

        lua_setfield(L, -2, IIFieldMeta->name);
    }
}

Variant Serializer::Deserialize(ITypeMeta* typeMeta)
{
    Variant object = typeMeta->Create();

    for (auto IIFieldMeta : typeMeta->fields)
    {
        lua_getfield(L, -1, IIFieldMeta->name);

        ITypeMeta* meta = IIFieldMeta->GetType();

        if (meta == TypeMeta<int>::Instance())
        {
            Variant value = lua_tointeger(L, -1);
            IIFieldMeta->set(object, value);
        }
        else if (meta == TypeMeta<char*>::Instance())
        {
            Variant value = lua_tolstring(L, -1, nullptr);
            IIFieldMeta->set(object, value);
        }
        else
        {
            Variant value = Deserialize(meta);
            IIFieldMeta->set(object, value);
        }

        lua_pop(L, 1);
    }

    return object;
}
