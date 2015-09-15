
#include "Serializer.h"
#include "FieldMeta.h"
#include "MethodMeta.h"

Serializer::Serializer()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    luaL_dofile(L, "Serializer.lua");
}

Serializer::~Serializer()
{
    lua_close(L);
    L = nullptr;
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
    else if (type == TypeMetaOf<std::string>())
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else if (type->isArray())
    {
        SerializeAsArray(object, type);
    }
    else if (type->isMap())
    {
        SerializeAsMap(object, type);
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

void Serializer::SerializeAsArray(Any& object, ITypeMeta* type)
{
    lua_newtable(L);

    auto arrayMeta = static_cast<IClassMeta*>(type);
    auto function = arrayMeta->functions["toAnyVector"];
    std::vector<Any> elements = function->Invoke(object);
    for (int i = 0; i < elements.size(); i++)
    {
        auto value = elements[i];
        Serialize(value, value.GetType());
        lua_seti(L, -2, i + 1);
    }
}

void Serializer::SerializeAsMap(Any& object, ITypeMeta* type)
{
    lua_newtable(L);

    auto mapMeta = static_cast<IClassMeta*>(type);
    auto function = mapMeta->functions["toAnyVector"];
    std::vector<Any> elements = function->Invoke(object);
    for (int i = 0; i < elements.size(); i += 2)
    {
        Serialize(elements[i], elements[i].GetType());
        Serialize(elements[i + 1], elements[i + 1].GetType());
        lua_settable(L, -3);
    }
}

//------------------------------------------------------------------------------------

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

Any Serializer::DeserializeAsArray(IClassMeta* arrayMeta)
{
    lua_pushnil(L);
    std::vector<Any> vector;
    while (lua_next(L, -2) != 0)
    {
        auto value = Deserialize(arrayMeta->valueType);
        vector.push_back(value);
        lua_pop(L, 1);
    }

    auto function = arrayMeta->functions["fromAnyVector"];
    std::vector<Any> args;
    args.push_back(vector);
    return function->Invoke(args);
}

Any Serializer::DeserializeAsMap(IClassMeta* mapMeta)
{
    lua_pushnil(L);
    std::vector<Any> vector;
    while (lua_next(L, -2) != 0)
    {
        auto value = Deserialize(mapMeta->valueType);
        lua_pop(L, 1);
        auto key = DeserializeUnknown();
        vector.push_back(key);
        vector.push_back(value);
    }

    auto function = mapMeta->functions["fromAnyVector"];
    std::vector<Any> args;
    args.push_back(vector);
    return function->Invoke(args);
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
    else if (type == TypeMetaOf<std::string>())
    {
        return std::string( lua_tostring(L, -1) );
    }
    else if (type->isArray())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsArray(classMeta);
    }
    else if (type->isMap())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsMap(classMeta);
    }
    else if (type->isClass())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsClass(classMeta);
    }

    return Any::empty;
}
