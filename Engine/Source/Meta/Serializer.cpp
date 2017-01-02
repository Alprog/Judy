
#include "Serializer.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include <cassert>
#include "List.h"
#include "ConstructorMeta.h"
#include "Meta/TypeMeta.h"
#include "Source/luainc.h"
#include "Object.h"

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

std::string Serializer::serialize(Any object)
{
    lua_getglobal(L, "TableToString");
    serialize(object, object.getType());
    lua_pcall(L, 1, 1, 0);
    return lua_tostring(L, -1);
}

void Serializer::serialize(Any object, ITypeMeta* type)
{
    auto flags = type->getFlags();
    if (flags & ITypeMeta::IsCustomSerializing)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        classMeta->functions["serialize"]->invoke(object, this);
    }
    else if (flags & ITypeMeta::IsPointer)
    {
        lua_newtable(L);
        lua_pushinteger(L, 1);

        auto pointeeType = type->getRunTimePointeeType(object);
        object = pointeeType->dereference(object);
        serialize(object, pointeeType);

        lua_settable(L, -3);
    }
    else if (type == typeMetaOf<std::string>())
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else if (flags & ITypeMeta::IsClass)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        serializeAsClass(object, classMeta);
    }
    else if (type == typeMetaOf<int>())
    {
        lua_pushinteger(L, object.as<int>());
    }
    else if (type == typeMetaOf<float>())
    {
        lua_pushnumber(L, object.as<float>());
    }
}

IFunctionMeta* findSerializeMethod(IClassMeta* classMeta)
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

IConstructorMeta* findSerializeConstructor(IClassMeta* classMeta)
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

void Serializer::serializeAsClass(Any& object, IClassMeta* classMeta)
{
    auto serializeMethod = findSerializeMethod(classMeta);
    if (serializeMethod != nullptr)
    {
        auto pointer = classMeta->makePointer(object);
        auto value = serializeMethod->invoke(pointer);
        serialize(value, value.getType());
        return;
    }

    lua_newtable(L);
    auto name = classMeta->name;
    lua_pushstring(L, name.c_str());
    lua_setfield(L, -2, "class");

    auto pointer = classMeta->makePointer(object);
    serializeClassFields(pointer, classMeta);
}

void Serializer::serializeClassFields(Any& pointer, IClassMeta* classMeta)
{
    auto fileds = classMeta->getFieldsWithAttribute("Serialize", true);

    for (auto fieldMeta : fileds)
    {
        Any value = fieldMeta->get(pointer);
        auto fieldType = fieldMeta->getType();
        serialize(value, fieldType);
        lua_setfield(L, -2, fieldMeta->name.c_str());
    }
    for (auto& baseType : classMeta->baseTypes)
    {
        if (baseType->isClass())
        {
            serializeClassFields(pointer, (IClassMeta*)baseType);
        }
    }
}

//------------------------------------------------------------------------------------

Any Serializer::deserialize(std::string text, ITypeMeta* typeMeta)
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
        return deserializeUnknown();
    }
    else
    {
        return deserialize(typeMeta);
    }
}

Any Serializer::deserializeUnknown()
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
        return deserializeUnknownTable();

    default:
        return Any::empty;
    }
}

Any Serializer::deserializeUnknownTable()
{
    lua_getfield(L, -1, "class");
    auto type = lua_type(L, -1);

    if (type == LUA_TSTRING)
    {
        std::string typeName = lua_tostring(L, -1);
        lua_pop(L, 1);
        for (auto type : Meta::getInstance()->types)
        {
            if (type->name == typeName)
            {
                if (type->isClass())
                {
                    auto classMeta = static_cast<IClassMeta*>(type);
                    return deserializeAsClass(classMeta);
                }
            }
        }
    }

    return Any::empty;
}

Any Serializer::deserialize(ITypeMeta* type)
{
    auto flags = type->getFlags();
    if (flags & ITypeMeta::IsCustomSerializing)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return classMeta->functions["deserialize"]->invoke(this);
    }
    else if (flags & ITypeMeta::IsPointer)
    {
        lua_pushinteger(L, 1);
        lua_gettable(L, -2);

        Any value;
        if (flags & ITypeMeta::IsPointerToPolymorhic)
        {
            value = deserializeUnknownTable();
        }
        else
        {
            value = deserialize(type->getPointeeType());
        }

        auto pointer = type->reference(value);
        value.detach(); // prevent destroy (keep data at heap)

        lua_pop(L, 1);
        return pointer;
    }
    else if (type == typeMetaOf<std::string>())
    {
        return std::string( lua_tostring(L, -1) );
    }
    else if (flags & ITypeMeta::IsClass)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return deserializeAsClass(classMeta);
    }
    else if (type == typeMetaOf<int>())
    {
        return lua_tointeger(L, -1);
    }
    else if (type == typeMetaOf<float>())
    {
        return (float)lua_tonumber(L, -1);
    }

    return Any::empty;
}

Any Serializer::deserializeAsClass(IClassMeta* classMeta)
{
    auto serializeConstructor = findSerializeConstructor(classMeta);
    if (serializeConstructor != nullptr)
    {
        auto argType = serializeConstructor->getArgTypes()[0];
        auto arg = deserialize(argType);
        return serializeConstructor->invoke(arg);
    }

    auto object = classMeta->create();
    auto pointer = classMeta->makePointer(object);
    deserializeClassFields(pointer, classMeta);
    return object;
}

void Serializer::deserializeClassFields(Any& pointer, IClassMeta* classMeta)
{
    auto fields = classMeta->getFieldsWithAttribute("Serialize", true);
    for (auto fieldMeta : fields)
    {
        lua_getfield(L, -1, fieldMeta->name.c_str());
        if (!lua_isnil(L, -1))
        {
            Any value = deserialize(fieldMeta->getType());
            fieldMeta->set(pointer, value);
        }
        lua_pop(L, 1);
    }
    for (auto& baseType : classMeta->baseTypes)
    {
        if (baseType->isClass())
        {
            deserializeClassFields(pointer, (IClassMeta*)baseType);
        }
    }
}
