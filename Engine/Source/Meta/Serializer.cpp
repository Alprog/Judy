
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
        Serialize(object, type->PointeeTypeMeta());
        lua_settable(L, -3);
        return;
    }

    if (type == TypeMetaOf<int>())
    {
        lua_pushinteger(L, object.as<int>());
    }
    else if (type == TypeMetaOf<float>())
    {
        lua_pushnumber(L, object.as<float>());
    }
    else if (type->isVector())
    {
        return lua_pushnumber(L, 0);
    }
    else if (type == TypeMetaOf<std::string>())
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else
    {
        lua_newtable(L);

        std::string modifiers = "";

        while (type->isPointer())
        {
            type = type->PointeeTypeMeta();
            object = type->Dereferencing(object);
            modifiers += '*';
        }

        auto name = type->name + modifiers;
        lua_pushstring(L, name.c_str());
        lua_setfield(L, -2, "@");

        if (type->isClass())
        {
            auto classMeta = dynamic_cast<IClassMeta*>(type);
            for (auto field : classMeta->fields)
            {
                Any value = field->get_local(object);
                auto fieldType = field->GetType();
                Serialize(value, fieldType);
                lua_setfield(L, -2, field->name);
            }
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
        std::string typeName = lua_tostring(L, -1);
        lua_pop(L, 1);
        for (auto type : Meta::Instance()->types)
        {
            if (type->name == typeName)
            {
                if (type->isClass())
                {
                    auto classMeta = dynamic_cast<IClassMeta*>(type);
                    return DeserializeAsClass(classMeta);
                }
            }
        }

    }

    return Any::empty;
}

Any Serializer::DeserializeAsClass(IClassMeta* classMeta)
{
    auto object = classMeta->CreateOnStack();

    for (auto fieldMeta : classMeta->fields)
    {
        printf("field: %s \n", fieldMeta->name);

        lua_getfield(L, -1, fieldMeta->name);
        Any value = Deserialize(fieldMeta->GetType());
        fieldMeta->set_local(object, value);
        lua_pop(L, 1);
    }

    return object;
}

Any Serializer::Deserialize(ITypeMeta* type)
{
    printf("DES %s\n", type->name.c_str());
    fflush(stdout);

    bool isPointer = type->isPointer();
    if (isPointer)
    {
        printf("POINTER\n");
        fflush(stdout);

        lua_pushinteger(L, 1);
        lua_gettable(L, -2);
        auto value = Deserialize(type->PointeeTypeMeta());

        printf("value %i\n", value.as<int>());
        fflush(stdout);

        value = type->MakePointerTo(value);

        printf("SUCCESS\n");
        fflush(stdout);

        lua_pop(L, 1);
        return value;
    }

    if (type == TypeMetaOf<int>())
    {
        return lua_tointeger(L, -1);
    }
    else if (type == TypeMetaOf<float>())
    {
        return (float)lua_tonumber(L, -1);
    }
    else if (type->isVector())
    {
        lua_tointeger(L, -1);
        return std::vector<int>();
    }
    else if (type == TypeMetaOf<std::string>())
    {
        return std::string( lua_tostring(L, -1) );
    }
    else if (type->isClass())
    {
        auto classMeta = dynamic_cast<IClassMeta*>(type);

        Any object = isPointer ? classMeta->CreateOnHeap() : classMeta->CreateOnStack();

        while (type->isPointer())
        {
            type = type->PointeeTypeMeta();
        }

        for (auto fieldMeta : classMeta->fields)
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

    return Any::empty;
}
