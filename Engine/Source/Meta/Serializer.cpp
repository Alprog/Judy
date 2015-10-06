
#include "Serializer.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include <cassert>
#include "List.h"
#include "ConstructorMeta.h"
#include "Meta/TypeMeta.h";
#include "Lua.h"

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
    else if (type->isList())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        classMeta->functions["serialize"]->Invoke(object, this);
    }
    else if (type->isClass())
    {
        SerializeAsClass(object, type);
    }
}

IFunctionMeta* FindSerializeMethod(IClassMeta* classMeta)
{
    for (auto& pair : classMeta->methods)
    {
        auto methodMeta = pair.second;
        if (methodMeta->hasAttribute("Serialize"))
        {
            return methodMeta;
        }
    }
    return nullptr;
}

IConstructorMeta* FindSerializeConstructor(IClassMeta* classMeta)
{
    for (auto constructor : classMeta->constructors)
    {
        if (constructor->hasAttribute("Serialize"))
        {
            return constructor;
        }
    }
    return nullptr;
}

void Serializer::SerializeAsClass(Any& object, ITypeMeta* type)
{
    auto classMeta = static_cast<IClassMeta*>(type);

    auto serializeMethod = FindSerializeMethod(classMeta);
    if (serializeMethod != nullptr)
    {
        auto pointer = type->MakePointer(object);
        auto value = serializeMethod->Invoke(pointer);
        Serialize(value, value.GetType());
        return;
    }

    lua_newtable(L);
    auto name = type->name;
    lua_pushstring(L, name.c_str());
    lua_setfield(L, -2, "class");

    for (auto& pair : classMeta->fields)
    {
        auto fieldMeta = pair.second;
        if (fieldMeta->hasAttribute("Serialize"))
        {
            Any value = fieldMeta->get_local(object);
            auto fieldType = fieldMeta->GetType();
            Serialize(value, fieldType);
            lua_setfield(L, -2, fieldMeta->name.c_str());
        }
    }
}

//------------------------------------------------------------------------------------

Any Serializer::Deserialize(std::string text, ITypeMeta* typeMeta)
{
    text = "return " + text;
    if (luaL_dostring(L, text.c_str()))
    {
        printf("%s \n", lua_tostring(L, -1));
        fflush(stdout);
        lua_pop(L, 1);
        return Any::empty;
    }
    if (typeMeta == nullptr)
    {
        return DeserializeUnknown();
    }
    else
    {
        return Deserialize(typeMeta);
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
        return (float)lua_tonumber(L, -1);

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
    auto serializeConstructor = FindSerializeConstructor(classMeta);
    if (serializeConstructor != nullptr)
    {
        auto argType = serializeConstructor->GetArgTypes()[0];
        auto arg = Deserialize(argType);
        return serializeConstructor->Invoke(arg);
    }

    auto object = classMeta->CreateOnStack();
    for (auto& pair : classMeta->fields)
    {
        auto fieldMeta = pair.second;
        if (fieldMeta->hasAttribute("Serialize"))
        {
            lua_getfield(L, -1, fieldMeta->name.c_str());
            Any value = Deserialize(fieldMeta->GetType());
            fieldMeta->set_local(object, value);
            lua_pop(L, 1);
        }
    }

    return object;
}

Any Serializer::Deserialize(ITypeMeta* type)
{
    if (type->isPointer())
    {
        lua_pushinteger(L, 1);
        lua_gettable(L, -2);
        Any value = Deserialize(type->GetPointeeType());
        auto pointer = type->MakePointer(value);
        value.Detach(); // prevent destroy (keep data at heap)
        lua_pop(L, 1);
        return pointer;
    }
    else if (type == TypeMetaOf<int>())
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
    else if (type->isList())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return classMeta->functions["deserialize"]->Invoke(this);
    }
    else if (type->isClass())
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsClass(classMeta);
    }

    return Any::empty;
}
