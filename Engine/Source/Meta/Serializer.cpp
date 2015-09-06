
#include "Serializer.h"
#include "ITypeMeta.h"
#include "Meta.h"

Serializer::Serializer(lua_State* L)
{
    this->L = L;
}

std::string Serializer::Serialize(Any object)
{
    lua_getglobal(L, "TableToString");
    Serialize(object, object.GetType());
    lua_pcall(L, 1, 1, 0);
    return lua_tostring(L, -1);
}

void Serializer::Serialize(Any object, ITypeMeta* type)
{
    if (type->isPointer())
    {
        lua_newtable(L);
        lua_pushinteger(L, 1);
        object = type->Dereference(object);
        Serialize(object, type->GetPointeeType());
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
        auto classMeta = static_cast<IClassMeta*>(type);

        auto method = classMeta->methods["size"];
        auto p = classMeta->MakePointer(object);
        std::vector<Any> args = { p };
        std::vector<int>::size_type size = method->Invoke(args);
        printf("%i \n", size);

        lua_pushnumber(L, 0);
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
            type = type->GetPointeeType();
            object = type->Dereference(object);
            modifiers += '*';
        }

        auto name = type->name + modifiers;
        lua_pushstring(L, name.c_str());
        lua_setfield(L, -2, "class");

        if (type->isClass())
        {
            auto classMeta = static_cast<IClassMeta*>(type);
            for (auto& pair : classMeta->fields)
            {
                auto field = pair.second;
                Any value = field->get_local(object);
                auto fieldType = field->GetType();
                Serialize(value, fieldType);
                lua_setfield(L, -2, field->name.c_str());
            }
        }

    }
}

Any Serializer::Deserialize(std::string text)
{
    text = "return " + text;
    if (luaL_dostring(L, text.c_str()))
    {
        printf("%s \n", lua_tostring(L, -1));
        fflush(stdout);
        lua_pop(L, 1);
        return Any::empty;
    }
    return DeserializeUnknown();
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
    lua_getfield(L, -1, "class");
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
                    auto classMeta = static_cast<IClassMeta*>(type);
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

    for (auto& pair : classMeta->fields)
    {
        auto fieldMeta = pair.second;
        lua_getfield(L, -1, fieldMeta->name.c_str());
        Any value = Deserialize(fieldMeta->GetType());
        fieldMeta->set_local(object, value);
        lua_pop(L, 1);
    }

    return object;
}

Any Serializer::Deserialize(ITypeMeta* type)
{
    bool isPointer = type->isPointer();
    if (isPointer)
    {
        printf("POINTER\n");
        fflush(stdout);

        lua_pushinteger(L, 1);
        lua_gettable(L, -2);
        auto value = Deserialize(type->GetPointeeType());

        printf("value %i\n", value.as<int>());
        fflush(stdout);

        value = type->MakePointer(value);

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
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsClass(classMeta);
    }

    return Any::empty;
}
