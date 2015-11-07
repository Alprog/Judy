
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"
#include "Lua.h"
#include "Object.h"

const int GETTER = 1;
const int SETTER = 2;

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
    Init();
}

int IndexFunction(lua_State* L)
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

int NewIndexFunction(lua_State* L)
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
    char* name = TypeMetaOf<T>()->name;
    return *(T**)luaL_checkudata(L, n, name);
}

inline Any GetArgument(lua_State* L, int index, ITypeMeta* typeMeta)
{
    if (typeMeta == TypeMetaOf<int>())
    {
        return lua_tointeger(L, index);
    }
    else if (typeMeta == TypeMetaOf<float>())
    {
        return (float)lua_tonumber(L, index);
    }
    else if (typeMeta == TypeMetaOf<char*>())
    {
        return lua_tostring(L, index);
    }
    else
    {
        void* p = *(void**)lua_touserdata(L, index);
        return p;
    }
}

inline void ProcessArguments(lua_State* L, IFunctionMeta* function, std::vector<Any>& args)
{
    auto types = function->GetArgTypes();
    int index = -types.size();
    for (auto typeMeta : types)
    {
        auto arg = GetArgument(L, index++, typeMeta);
        args.push_back(arg);
    }
}

void pushObject(lua_State* L, Object* pointer, std::string className)
{
    if (pointer->luaObject != nullptr)
    {
        lua_pushuserdata(L, pointer->luaObject); // U
        return;
    }

    auto udata = (void**)lua_newuserdata(L, sizeof(void*)); // U
    *udata = pointer;
    pointer->luaObject = udata;

    // set metatable
    luaL_getmetatable(L, "Userdata"); // UM
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

inline void ProcessResult(lua_State* L, Any& result, ITypeMeta* type)
{
    if (type == TypeMetaOf<int>())
    {
        lua_pushinteger(L, result.as<int>());
    }
    else if (type == TypeMetaOf<float>())
    {
        lua_pushnumber(L, result.as<float>());
    }
    else if (type == TypeMetaOf<char*>())
    {
        lua_pushstring(L, result.as<char*>());
    }
    else
    {
        if (type->isPointer())
        {
            auto pointer = result.as<Object*>();

            auto className = pointer->luaClass;
            if (className.empty())
            {
                className = type->GetRunTimePointeeType(pointer)->name;
            }

            pushObject(L, pointer, className);
        }
        else
        {
            // todo: send full userdata
            throw std::runtime_error("not implemented");
        }
    }
}

int GetterInvoker(lua_State* L)
{
    auto field = (IFieldMeta*)lua_touserdata(L, lua_upvalueindex(1));
    Any object = *(void**)lua_touserdata(L, -1);
    Any result = field->Get(object);
    ProcessResult(L, result, field->GetType());
    return 1;
}

int SetterInvoker(lua_State* L)
{
    auto field = (IFieldMeta*)lua_touserdata(L, lua_upvalueindex(1));
    Any object = *(void**)lua_touserdata(L, -2);
    Any value = GetArgument(L, -1, field->GetType());
    field->Set(object, value);
    return 0;
}

int FunctionInvoker(lua_State* L)
{
    auto function = (IFunctionMeta*)lua_touserdata(L, lua_upvalueindex(1));

    std::vector<Any> args = {};
    ProcessArguments(L, function, args);

    auto returnType = function->GetReturnType();
    if (returnType == nullptr)
    {
        function->Invoke(args);
        return 0;
    }
    else
    {
        auto result = function->Invoke(args);
        ProcessResult(L, result, returnType);
        return 1;
    }
}

std::string forceLuaClass = "";

int SetForceLuaClass(lua_State* L)
{
    forceLuaClass = lua_tostring(L, -1);
    return 0;
}

int ConstructorInvoker(lua_State* L)
{
    auto constructor = (IConstructorMeta*)lua_touserdata(L, lua_upvalueindex(1));
    std::vector<Any> args = {};
    ProcessArguments(L, constructor, args);
    auto result = constructor->New(args);

    if (!forceLuaClass.empty())
    {
        result.as<Object*>()->luaClass = forceLuaClass;
        forceLuaClass.clear();
    }

    auto type = constructor->GetNewType();
    ProcessResult(L, result, type);
    return 1;
}

void LuaBinder::Init()
{
    // metatable for userdata
    auto name = "Userdata";
    luaL_newmetatable(L, name); // M
    lua_pushcfunction(L, IndexFunction); // MF
    lua_setfield(L, -2, "__index");  // M
    lua_pushcfunction(L, NewIndexFunction);  // MF
    lua_setfield(L, -2, "__newindex");  // M
    lua_setglobal(L, name); //

    // setForceLuaClass function
    lua_pushcfunction(L, SetForceLuaClass);
    lua_setglobal(L, "SetForceLuaClass");
}

void LuaBinder::Bind(Meta* meta)
{
    for (auto& typeMeta : meta->types)
    {
        if (typeMeta->getFlags() & ITypeMeta::IsClass)
        {
            auto classMeta = static_cast<IClassMeta*>(typeMeta);
            BindClass(classMeta);
        }
    }
}

void LuaBinder::BindClass(IClassMeta* classMeta)
{
    auto className = classMeta->name.c_str();

    luaL_newmetatable(L, className); // M

    for (auto constructor : classMeta->constructors)
    {
        int argCount = constructor->GetArgCount();
        std::string name = "new" + std::to_string(argCount);
        BindHelper(name, ConstructorInvoker, constructor);
    }

    for (auto& pair : classMeta->methods)
    {
        auto method = pair.second;
        BindHelper(method->name, FunctionInvoker, method);
    }

    for (auto& pair : classMeta->functions)
    {
        auto function = pair.second;
        BindHelper(function->name, FunctionInvoker, function);
    }

    // fields
    {
        for (auto& pair : classMeta->fields)
        {
            auto field = pair.second;

            lua_newtable(L); // MP
            BindHelper("GET", GetterInvoker, field);
            BindHelper("SET", SetterInvoker, field);

            lua_setfield(L, -2, field->name.c_str()); // M
        }
    }

    // base type
    if (classMeta->baseTypes.size() > 1)
    {
        throw new std::runtime_error("multiple inheritance not implemented");
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

void LuaBinder::BindHelper(std::string name, luaCFunction closure, void* upvalue)
{
    lua_pushlightuserdata(L, (void*)upvalue); // ML
    lua_pushcclosure(L, closure, 1); // MC
    lua_setfield(L, -2, name.c_str()); // M
}
