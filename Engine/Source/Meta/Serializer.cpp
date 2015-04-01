
#include "Serializer.h"
#include "ITypeMeta.h"
#include "Meta.h"

void Serializer::Serialize(Any object, ITypeMeta* type)
{
    if (type->isPointer())
    {
        lua_newtable(L);
        lua_pushinteger(L, 1);
        object = type->Dereferencing(object);
        Serialize(object, type->DerefType());
        lua_settable(L, -3);
        return;
    }

    if (type == &TypeMeta<int>::instance)
    {
        lua_pushnumber(L, object.as<int>());
    }
    else if (type->isVector())
    {
        return lua_pushnumber(L, 0);
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
            Any value = field->get_local(object);
            auto fieldType = field->GetType();
            Serialize(value, fieldType);
            lua_setfield(L, -2, field->name);
        }
    }
}

Any Serializer::DeserializeUnknown()
{
    auto type = lua_type(L, -1);

    switch (type)
    {
    case LUA_TBOOLEAN:
        return lua_toboolean(L, -1);

    case LUA_TNUMBER:
        return lua_tonumber(L, -1);

    case LUA_TSTRING:
        return std::string { lua_tostring(L, -1) };

    case LUA_TTABLE:
        return DeserializeUnknownTable();

    default:
        return Any::empty;
    }
}

Any Serializer::DeserializeUnknownTable()
{
    lua_getfield(L, -1, "@");
    auto type = lua_type(L, -1);

    if (type == LUA_TSTRING)
    {
        const char* typeName = lua_tostring(L, -1);
        lua_pop(L, 1);
        for (auto type : Meta::Instance()->Types)
        {
            if (!strcmp(type->name, typeName))
            {
                return DeserializeAsClass(type);
            }
        }

    }

    return Any::empty;
}

Any Serializer::DeserializeAsClass(ITypeMeta* type)
{
    auto object = type->CreateOnStack();

    for (auto fieldMeta : type->fields)
    {
        printf(fieldMeta->name);

        lua_getfield(L, -1, fieldMeta->name);
        Any value = Deserialize(fieldMeta->GetType());
        fieldMeta->set_local(object, value);
        lua_pop(L, 1);
    }

    return object;
}

Any Serializer::Deserialize(ITypeMeta* type)
{
    printf("DES %s\n", type->name);
    fflush(stdout);

    bool isPointer = type->isPointer();
    if (isPointer)
    {
        printf("POINTER\n");
        fflush(stdout);

        lua_pushinteger(L, 1);
        lua_gettable(L, -2);
        auto value = Deserialize(type->DerefType());

        printf("value %i\n", value.as<int>());
        fflush(stdout);

        value = type->MakePointerTo(value);

        printf("SUCCESS\n");
        fflush(stdout);

        lua_pop(L, 1);
        return value;
    }

    if (type == &TypeMeta<int>::instance)
    {
        return lua_tointeger(L, -1);
    }
    else if (type->isVector())
    {
        lua_tointeger(L, -1);
        return std::vector<int>();
    }
    else if (type == &TypeMeta<std::string>::instance)
    {
        return std::string( lua_tostring(L, -1) );
    }
    else
    {
        Any object = isPointer ? type->CreateOnHeap() : type->CreateOnStack();

        while (type->isPointer())
        {
            type = type->DerefType();
        }

        for (auto fieldMeta : type->fields)
        {
            printf("F %s\n", fieldMeta->name);
            fflush(stdout);

            lua_getfield(L, -1, fieldMeta->name);
            Any value = Deserialize(fieldMeta->GetType());
            if (isPointer)
            {
                fieldMeta->set(object, value);
            }
            else
            {
                fieldMeta->set_local(object, value);
            }
            lua_pop(L, 1);
        }

        return object;
    }
}
