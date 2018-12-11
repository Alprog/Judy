
#include <Binder.h>

#include <string.h>
#include "Source/luainc.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"
#include "Object.h"
#include "Ref.h"

const int GETTER = 1;
const int SETTER = 2;

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
    init();
}

int indexFunction(lua_State* L)
{
    // UK (userdata, key)
    lua_getuservalue(L, -2); // UKP (..., peertable)

    // inspect peer
    lua_pushvalue(L, -2); // UKPK
    lua_rawget(L, -2); // UKP?
    if (!lua_isnil(L, -1))
    {
        lua_replace(L, -4); // ?KP
        lua_pop(L, 2); // ?
        return 1;
    }
    lua_pop(L, 1); // UKP

    lua_getmetatable(L, -1); // UKPM

    // inspect meta
    lua_pushvalue(L, -3); // UKPMK
    lua_gettable(L, -2); // UKPM?

    // if property then call getter
    if (lua_istable(L, -1))
    {
        lua_getfield(L, -1, "GET"); // UKPMTF
        lua_insert(L, -6); // FUKPMT
        lua_pop(L, 4); // FU
        lua_call(L, 1, 1); // ?
        return 1;
    }

    lua_replace(L, -5); // ?KPM
    lua_pop(L, 3); // ?
    return 1;
}

int newIndexFunction(lua_State* L)
{
    // UKV (userdata, key, value)

    lua_getuservalue(L, -3); // UKVP (..., peertable)

    // check setter in meta
    lua_getmetatable(L, -1); // UKVPM
    lua_pushvalue(L, -4);    // UKVPMK
    lua_gettable(L, -2);     // UKVPM?

    // if property than call setter
    if (lua_istable(L, -1))
    {
        lua_getfield(L, -1, "SET"); // UKVPMTF
        lua_insert(L, -7); // FUKVPMT
        lua_pop(L, 3); // FUKV
        lua_remove(L, -2); // FUV
        lua_call(L, 2, 0); //
        return 0;
    }
    lua_pop(L, 2); // UKVP

    // set to peer
    lua_insert(L, -3); // UPKV
    lua_rawset(L, -3); // UP
    lua_pop(L, 2); //
    return 0;
}

template <typename T>
T* CheckType(lua_State* L, int n)
{
    char* name = typeMetaOf<T>()->name;
    return *(T**)luaL_checkudata(L, n, name);
}

inline Any getArgument(lua_State* L, int index, ITypeMeta* typeMeta)
{
    if (typeMeta == typeMetaOf<int>())
    {
        return lua_tointeger(L, index);
    }
    else if (typeMeta == typeMetaOf<float>())
    {
        return (float)lua_tonumber(L, index);
    }
    if (typeMeta == typeMetaOf<bool>())
    {
        return lua_toboolean(L, index);
    }
    else if (typeMeta == typeMetaOf<char*>())
    {
        return lua_tostring(L, index);
    }
    else if (typeMeta->isPointer())
    {
        if (lua_isnil(L, index))
        {
            void* p = nullptr;
            return p;
        }
        else
        {
            void* p = *(void**)lua_touserdata(L, index);
            return p;
        }
    }
    else if (typeMeta->isEnum())
    {
        return lua_tointeger(L, index);
    }
    else
    {
        Any p = *(void**)lua_touserdata(L, index);
        return typeMeta->dereference(p);
    }
}

inline void processArguments(lua_State* L, IFunctionMeta* function, std::vector<Any>& args)
{
    auto types = function->getArgTypes();
    int index = -(int)types.size();
    for (auto typeMeta : types)
    {
        auto arg = getArgument(L, index++, typeMeta);
        args.push_back(arg);
    }
}

void setMetatable(lua_State* L, std::string className, bool gc)
{
    // set metatable
    luaL_getmetatable(L, gc ? "Userdata" : "Value"); // UM
    lua_setmetatable(L, -2); // U

    // create peer table
    {
        lua_newtable(L); // UP

        lua_getglobal(L, className.c_str()); // UPM
        if (lua_isnil(L, -1))
        {
            throw std::runtime_error("unknown type");
        }
        lua_setmetatable(L, -2); // UP

        lua_setuservalue(L, -2); // U
    }
}

void pushValue(lua_State* L, void* pointer, ITypeMeta* type)
{
    auto dataSize = type->getSize();
    auto udata = (void**)lua_newuserdata(L, sizeof(void*) + dataSize);
    void* dataStart = udata + 1;
    *udata = dataStart;
    memcpy(dataStart, pointer, dataSize);

    setMetatable(L, type->name, false);
}

void pushPointer(lua_State* L, void* pointer, ITypeMeta* type)
{
    auto udata = (void**)lua_newuserdata(L, sizeof(void*)); // U
    *udata = pointer;
    setMetatable(L, type->name, false);
}

void pushObjectPointer(lua_State* L, Object* pointer, std::string className)
{
    if (pointer->luaObject != nullptr)
    {
        lua_pushuserdata(L, pointer->luaObject); // U
        return;
    }

    auto udata = (void**)lua_newuserdata(L, sizeof(void*)); // U
    *udata = pointer;
    pointer->luaObject = udata;

    setMetatable(L, className, true);
}

inline void processResult(lua_State* L, Any& result, ITypeMeta* type)
{
    auto flags = type->getFlags();

    if (flags & ITypeMeta::Flags::IsBuiltIn)
    {
        if (type == typeMetaOf<bool>())
        {
            lua_pushboolean(L, result.as<bool>());
        }
        else if (type == typeMetaOf<int>())
        {
            lua_pushinteger(L, result.as<int>());
        }
        else if (type == typeMetaOf<float>())
        {
            lua_pushnumber(L, result.as<float>());
        }
        else if (type == typeMetaOf<char*>())
        {
            lua_pushstring(L, result.as<char*>());
        }
        else
        {
            throw std::runtime_error("unknown built in type");
        }
    }
    else if (flags & ITypeMeta::Flags::IsPointer)
    {
        if (flags & ITypeMeta::Flags::IsPointerToObject)
        {
            auto pointer = result.as<Object*>();

            auto className = pointer->luaClass;
            if (className.empty())
            {
                className = type->getRunTimePointeeType(result)->name;
            }

            pushObjectPointer(L, pointer, className);
        }
        else
        {
            pushPointer(L, result.as<void*>(), type->getPointeeType());
        }
    }
    else
    {
        pushValue(L, result.getAddress(), type);
    }
}

int getterInvoker(lua_State* L)
{
    auto field = (IFieldMeta*)lua_touserdata(L, lua_upvalueindex(1));
    Any object = *(void**)lua_touserdata(L, -1);
    Any result = field->get(object);
    processResult(L, result, field->getType());
    return 1;
}

int setterInvoker(lua_State* L)
{
    auto field = (IFieldMeta*)lua_touserdata(L, lua_upvalueindex(1));
    Any object = *(void**)lua_touserdata(L, -2);
    Any value = getArgument(L, -1, field->getType());
    field->set(object, value);
    return 0;
}

int functionInvoker(lua_State* L)
{
    auto function = (IFunctionMeta*)lua_touserdata(L, lua_upvalueindex(1));

    std::vector<Any> args = {};
    processArguments(L, function, args);

    auto returnType = function->getReturnType();
    if (returnType == nullptr)
    {
        function->invoke(args);
        return 0;
    }
    else
    {
        auto result = function->invoke(args);
        processResult(L, result, returnType);
        return 1;
    }
}

std::string forceLuaClass = "";

int setForceLuaClass(lua_State* L)
{
    forceLuaClass = lua_tostring(L, -1);
    return 0;
}

int constructorInvoker(lua_State* L)
{
    auto constructor = (IConstructorMeta*)lua_touserdata(L, lua_upvalueindex(1));
    std::vector<Any> args = {};
    processArguments(L, constructor, args);
    auto result = constructor->New(args);

    if (!forceLuaClass.empty())
    {
        result.as<Object*>()->luaClass = forceLuaClass;
        forceLuaClass.clear();
    }

    auto type = constructor->getNewType();
    processResult(L, result, type);
    return 1;
}

void LuaBinder::init()
{
    // metatable for object userdata
    auto name = "Userdata";
    luaL_newmetatable(L, name); // M
    lua_pushcfunction(L, indexFunction); // MF
    lua_setfield(L, -2, "__index");  // M
    lua_pushcfunction(L, newIndexFunction);  // MF
    lua_setfield(L, -2, "__newindex");  // M
    lua_pushcfunction(L, Object::GC);  // MF
    lua_setfield(L, -2, "__gc");  // M
    lua_setglobal(L, name); //

    // metatable for value userdata
    name = "Value";
    luaL_newmetatable(L, name); // M
    lua_pushcfunction(L, indexFunction); // MF
    lua_setfield(L, -2, "__index");  // M
    lua_pushcfunction(L, newIndexFunction);  // MF
    lua_setfield(L, -2, "__newindex");  // M
    lua_setglobal(L, name); //

    // setForceLuaClass function
    lua_pushcfunction(L, setForceLuaClass);
    lua_setglobal(L, "setForceLuaClass");
}

void LuaBinder::bind(Meta* meta)
{
    for (auto& typeMeta : meta->types)
    {
        if (typeMeta->getFlags() & ITypeMeta::IsClass)
        {
            auto classMeta = static_cast<IClassMeta*>(typeMeta);
            bindClass(classMeta);
        }
    }
}

void LuaBinder::bindClass(IClassMeta* classMeta)
{
    auto className = classMeta->name.c_str();

    luaL_newmetatable(L, className); // M

    for (auto constructor : classMeta->constructors)
    {
        size_t argCount = constructor->getArgCount();
        std::string name = "new" + std::to_string(argCount);
        bindHelper(name, constructorInvoker, constructor);
    }

    for (auto& pair : classMeta->methods)
    {
        auto method = pair.second;
        bindHelper(method->name, functionInvoker, method);
    }

    for (auto& pair : classMeta->functions)
    {
        auto function = pair.second;
        bindHelper(function->name, functionInvoker, function);
    }

    // fields
    {
        for (auto& pair : classMeta->fields)
        {
            auto field = pair.second;

            lua_newtable(L); // MP
            bindHelper("GET", getterInvoker, field);
            bindHelper("SET", setterInvoker, field);

            lua_setfield(L, -2, field->name.c_str()); // M
        }
    }

    // base type
    if (classMeta->baseTypes.size() > 1)
    {
        throw std::runtime_error("multiple inheritance not implemented");
    }
    for (auto baseType : classMeta->baseTypes)
    {
        if (!baseType->name.empty())
        {
            printf("%s %s\n", className, baseType->name.c_str());
            luaL_newmetatable(L, baseType->name.c_str()); // MB
            lua_setmetatable(L, -2); // M
        }
    }

    //
    lua_pushvalue(L, -1); // MM
    lua_setfield(L, -2, "__index"); // M
    //lua_pushvalue(L, -1); // MM
    //lua_setfield(L, -2, "__newindex"); // M

    lua_setglobal(L, className);
}

void LuaBinder::bindHelper(std::string name, luaCFunction closure, void* upvalue)
{
    lua_pushlightuserdata(L, (void*)upvalue); // ML
    lua_pushcclosure(L, closure, 1); // MC
    lua_setfield(L, -2, name.c_str()); // M
}
