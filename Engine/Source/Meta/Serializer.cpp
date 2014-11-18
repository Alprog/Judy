
#include "Serializer.h"
#include "TypeMeta.h"

void Serializer::Serialize(Variant object, ITypeMeta* type)
{
    if (type == &TypeMeta<int>::instance)
    {
        lua_pushnumber(L, object.as<int>());
    }
    else if (type == &TypeMeta<std::string>::instance)
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else
    {
        lua_newtable(L);

        std::string modifiers = "";

        while (type->isPointer())
        {
            type = type->DerefType();
            object = type->Dereferencing(object);
            modifiers += '*';
        }

        auto name = type->name + modifiers;
        lua_pushstring(L, name.c_str());
        lua_setfield(L, -2, "@");
        for (auto field : type->fields)
        {
            Variant value = field->get_local(object);
            auto fieldType = field->GetType();
            Serialize(value, fieldType);
            lua_setfield(L, -2, field->name);
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
