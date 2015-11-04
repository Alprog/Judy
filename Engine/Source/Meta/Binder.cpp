
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"
#include "Lua.h"

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
}

template <typename T>
T* CheckType(lua_State* L, int n)
{
    char* name = TypeMetaOf<T>()->name;
    return *(T**)luaL_checkudata(L, n, name);
}

inline void ProcessArguments(lua_State* L, IFunctionMeta* function, std::vector<Any>& args)
{
    auto types = function->GetArgTypes();
    int index = -types.size();
    for (auto argType : types)
    {
        if (argType == TypeMetaOf<int>())
        {
            args.push_back(lua_tointeger(L, index++));
        }
        else if (argType == TypeMetaOf<float>())
        {
            args.push_back((float)lua_tonumber(L, index++));
        }
        else if (argType == TypeMetaOf<char*>())
        {
            args.push_back(lua_tostring(L, index++));
        }
        else
        {
            void* p = *(void**)lua_touserdata(L, index++);
            args.push_back(p);
        }
    }
}

//void* p = *(void**)lua_touserdata(L, -3); // KV
//lua_getmetatable(L, -3); // TKVM

int NewIndexFunction(lua_State* L)
{
    // UKV (userdata, key, value)

    lua_getmetatable(L, -3); // UKVP (..., peertable)
    lua_insert(L, -3); // UPKV

    lua_rawset(L, -3); // UP
    lua_pop(L, 2); //
    return 0;
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

        // create peer table
        lua_newtable(L); // TUP
        lua_pushvalue(L, -1); // TUPP
        lua_setfield(L, -2, "__index"); // TUP
        lua_pushvalue(L, -1); // TUPP
        lua_setfield(L, -2, "__newindex"); // TUP


        lua_newtable(L);         // TUV
        lua_setuservalue(L, -1); // TU

        // set metatable (todo: rtti for actual type)
        luaL_getmetatable(L, type->name.c_str()); // TUPM
        if (lua_isnil(L, -1))
        {
            throw std::runtime_error("unknown type");
        }
        lua_setmetatable(L, -2); // TUP

        lua_setmetatable(L, -2); // TU

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
    Any object = *(void**)lua_touserdata(L, 1);
    Any result = field->Get(object);
    ProcessResult(L, result, field->GetType());
    return 1;
}

int SetterInvoker(lua_State* L)
{

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
    auto function = (IFunctionMeta*)lua_touserdata(L, lua_upvalueindex(1));
    std::vector<Any> args = {};
    ProcessArguments(L, function, args);

    auto constructor = dynamic_cast<IConstructorMeta*>(function);
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
//    {
//        lua_newtable(L); // MG
//        lua_newtable(L); // MGS

//        for (auto& pair : classMeta->fields)
//        {
//            auto field = pair.second;
//            BindHelper(-2, field->name, GetterInvoker, field);
//            BindHelper(-1, field->name, SetterInvoker, field);
//        }

//        lua_setfield(L, -3, "__set"); // MG
//        lua_setfield(L, -2, "__get"); // M
//    }

    //
    lua_pushvalue(L, -1); // MM
    lua_setfield(L, -2, "__index"); // M
    //lua_pushvalue(L, -1); // MM
    //lua_setfield(L, -2, "__newindex"); // M

    lua_setglobal(L, className);
}

void LuaBinder::BindHelper(int index, std::string name, luaCFunction closure, IFunctionMeta* upvalue)
{
    // T...
    lua_pushlightuserdata(L, upvalue); // T...L
    lua_pushcclosure(L, closure, 1); // T...C
    lua_setfield(L, index - 1, name.c_str()); // T...
}
