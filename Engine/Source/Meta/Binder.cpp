
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"
#include "Lua.h"

const int GETTER = 1;
const int SETTER = 2;

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

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
    auto name = "Userdata";
    luaL_newmetatable(L, name); // M

    lua_pushcfunction(L, IndexFunction); // MF
    lua_setfield(L, -2, "__index");  // M
    lua_pushcfunction(L, NewIndexFunction);  // MF
    lua_setfield(L, -2, "__newindex");  // M

    lua_setglobal(L, name); //
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

void pushUserdata(lua_State* L, void* pointer, ITypeMeta* type)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "UDATA"); // T
    lua_pushlightuserdata(L, pointer); // TL
    lua_gettable(L, -2); // T?

    if (lua_isuserdata(L, -1))
    {
        // TU
        lua_remove(L, -2); // U
    }
    else
    {
        // T?
        lua_pop(L, 1); // T

        auto udata = (void**)lua_newuserdata(L, sizeof(void*)); // TU
        *udata = pointer;

        // set metatable
        luaL_getmetatable(L, "Userdata"); // TUM
        lua_setmetatable(L, -2); // TU

        // create peer table
        lua_newtable(L); // TUP
        // set metatable (todo: rtti for actual type)
        luaL_getmetatable(L, type->name.c_str()); // TUPM
        if (lua_isnil(L, -1))
        {
            throw std::runtime_error("unknown type");
        }
        lua_setmetatable(L, -2); // TUP
        lua_setuservalue(L, -2); // TU

        lua_pushlightuserdata(L, pointer); // TUL
        lua_pushvalue(L, -2); // TULU
        lua_rawset(L, -4); // TU
        lua_remove(L, -2); // U
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
            auto pointer = result.as<void*>();
            auto pointeeType = type->GetPointeeType();
            pushUserdata(L, pointer, pointeeType);
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

int NewInvoker(lua_State* L)
{
    auto constructor = (IConstructorMeta*)lua_touserdata(L, lua_upvalueindex(1));
    std::vector<Any> args = {};
    ProcessArguments(L, constructor, args);
    auto result = constructor->New(args);
    auto type = constructor->GetNewType();
    ProcessResult(L, result, type);
    return 1;
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
        BindHelper(-1, name, NewInvoker, constructor);
    }

    for (auto& pair : classMeta->methods)
    {
        auto method = pair.second;
        BindHelper(-1, method->name, FunctionInvoker, method);
    }

    for (auto& pair : classMeta->functions)
    {
        auto function = pair.second;
        BindHelper(-1, function->name, FunctionInvoker, function);
    }

    // fields
    {
        for (auto& pair : classMeta->fields)
        {
            auto field = pair.second;

            lua_newtable(L); // MP
            BindHelper(-1, "GET", GetterInvoker, field);
            BindHelper(-1, "SET", SetterInvoker, field);

            lua_setfield(L, -2, field->name.c_str()); // M
        }
    }

    //
    lua_pushvalue(L, -1); // MM
    lua_setfield(L, -2, "__index"); // M
    //lua_pushvalue(L, -1); // MM
    //lua_setfield(L, -2, "__newindex"); // M

    lua_setglobal(L, className);
}

void LuaBinder::BindHelper(int index, std::string name, luaCFunction closure, void* upvalue)
{
    // T...
    lua_pushlightuserdata(L, (void*)upvalue); // T...L
    lua_pushcclosure(L, closure, 1); // T...C
    lua_setfield(L, index - 1, name.c_str()); // T...
}
