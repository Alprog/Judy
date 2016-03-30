
#include "Serializer.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include <cassert>
#include "List.h"
#include "ConstructorMeta.h"
#include "Meta/TypeMeta.h"
#include "Lua.h"
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

std::string Serializer::Serialize(Any object)
{
    lua_getglobal(L, "TableToString");
    Serialize(object, object.GetType());
    lua_pcall(L, 1, 1, 0);
    return lua_tostring(L, -1);
}

void Serializer::Serialize(Any object, ITypeMeta* type)
{
    auto flags = type->getFlags();
    if (flags & ITypeMeta::IsCustomSerializing)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        classMeta->functions["serialize"]->Invoke(object, this);
    }
    else if (flags & ITypeMeta::IsPointer)
    {
        lua_newtable(L);
        lua_pushinteger(L, 1);

        auto pointeeType = type->GetRunTimePointeeType(object);
        object = pointeeType->Dereference(object);
        Serialize(object, pointeeType);

        lua_settable(L, -3);
    }
    else if (type == TypeMetaOf<std::string>())
    {
        lua_pushstring(L, object.as<std::string>().c_str());
    }
    else if (flags & ITypeMeta::IsClass)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        SerializeAsClass(object, classMeta);
    }
    else if (type == TypeMetaOf<int>())
    {
        lua_pushinteger(L, object.as<int>());
    }
    else if (type == TypeMetaOf<float>())
    {
        lua_pushnumber(L, object.as<float>());
    }
}

IFunctionMeta* FindSerializeMethod(IClassMeta* classMeta)
{
    for (auto& pair : classMeta->methods)
    {
        auto methodMeta = pair.second;
        if (methodMeta->HasAttribute("Serialize"))
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
        if (constructor->HasAttribute("Serialize"))
        {
            return constructor;
        }
    }
    return nullptr;
}

void Serializer::SerializeAsClass(Any& object, IClassMeta* classMeta)
{
    auto serializeMethod = FindSerializeMethod(classMeta);
    if (serializeMethod != nullptr)
    {
        auto pointer = classMeta->MakePointer(object);
        auto value = serializeMethod->Invoke(pointer);
        Serialize(value, value.GetType());
        return;
    }

    lua_newtable(L);
    auto name = classMeta->name;
    lua_pushstring(L, name.c_str());
    lua_setfield(L, -2, "class");

    auto pointer = classMeta->MakePointer(object);
    SerializeClassFields(pointer, classMeta);
}

void Serializer::SerializeClassFields(Any& pointer, IClassMeta* classMeta)
{
    auto fileds = classMeta->GetFieldsWithAttribute("Serialize", true);

    for (auto fieldMeta : fileds)
    {
        Any value = fieldMeta->Get(pointer);
        auto fieldType = fieldMeta->GetType();
        Serialize(value, fieldType);
        lua_setfield(L, -2, fieldMeta->name.c_str());
    }
    for (auto& baseType : classMeta->baseTypes)
    {
        if (baseType->isClass())
        {
            SerializeClassFields(pointer, (IClassMeta*)baseType);
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

Any Serializer::Deserialize(ITypeMeta* type)
{
    auto flags = type->getFlags();
    if (flags & ITypeMeta::IsCustomSerializing)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return classMeta->functions["deserialize"]->Invoke(this);
    }
    else if (flags & ITypeMeta::IsPointer)
    {
        lua_pushinteger(L, 1);
        lua_gettable(L, -2);

        auto pointeeType = type->GetPointeeType();

        Any value;
        if (flags & ITypeMeta::IsPointerToPolymorhic)
        {
            value = DeserializeUnknownTable();
        }
        else
        {
            value = Deserialize(pointeeType);
        }

        auto pointer = type->Create(value);
        value.Detach(); // prevent destroy (keep data at heap)

        //auto p = type->CreateOnStack();

        lua_pop(L, 1);
        return pointer;
    }
    else if (type == TypeMetaOf<std::string>())
    {
        return std::string( lua_tostring(L, -1) );
    }
    else if (flags & ITypeMeta::IsClass)
    {
        auto classMeta = static_cast<IClassMeta*>(type);
        return DeserializeAsClass(classMeta);
    }
    else if (type == TypeMetaOf<int>())
    {
        return lua_tointeger(L, -1);
    }
    else if (type == TypeMetaOf<float>())
    {
        return (float)lua_tonumber(L, -1);
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


    auto pointer = classMeta->MakePointer(object);
    DeserializeClassFields(pointer, classMeta);
    return object;
}

void Serializer::DeserializeClassFields(Any& pointer, IClassMeta* classMeta)
{
    auto fields = classMeta->GetFieldsWithAttribute("Serialize", true);
    for (auto fieldMeta : fields)
    {
        lua_getfield(L, -1, fieldMeta->name.c_str());
        Any value = Deserialize(fieldMeta->GetType());
        fieldMeta->Set(pointer, value);
        lua_pop(L, 1);
    }
    for (auto& baseType : classMeta->baseTypes)
    {
        if (baseType->isClass())
        {
            DeserializeClassFields(pointer, (IClassMeta*)baseType);
        }
    }
}
