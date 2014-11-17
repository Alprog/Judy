
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(Variant object, ITypeMeta* const typeMeta)
{
    if (typeMeta == &TypeMeta<int>::instance)
    {
        lua_pushnumber(L, object.as<int>());
    }
    else if (typeMeta == &TypeMeta<std::string>::instance)
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else if (typeMeta == &TypeMeta<char*>::instance)
    {
        lua_pushstring(L, object.as<char*>());
    }
    else
    {
        lua_newtable(L);

        for (auto fieldMeta : typeMeta->fields)
        {
            Variant value = fieldMeta->get_local(object);

            auto type = fieldMeta->GetType();

            if (type->isPointer())
            {
                Variant v = type->Dereferencing(value);

                value = v;

                Serialize(v, fieldMeta->GetType());
                lua_setfield(L, -2, fieldMeta->name);
            }
            else
            {
                Serialize(value, fieldMeta->GetType());
                lua_setfield(L, -2, fieldMeta->name);
            }
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
        Variant object = typeMeta->CreateOnStack();

        for (auto fieldMeta : typeMeta->fields)
        {
            if (fieldMeta->GetType()->isPointer())
            {

            }
            else
            {
                lua_getfield(L, -1, fieldMeta->name);
                Variant value = Deserialize(fieldMeta->GetType());
                fieldMeta->set_local(object, value);
                lua_pop(L, 1);
            }
        }

        return object;
    }
}
