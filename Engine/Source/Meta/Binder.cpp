
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

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

int GetterInvoker(lua_State* L)
{
    auto field = *(IFieldMeta**)lua_touserdata(L, lua_upvalueindex(1));

    void* object = *(void**)lua_touserdata(L, 1);

    field->get(object);

    return 1;
}

int FunctionInvoker(lua_State* L)
{
    auto method = *(IFunctionMeta**)lua_touserdata(L, lua_upvalueindex(1));

    int index = 1;
    std::vector<Any> args = {};
    for (auto argType : method->GetArgTypes())
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

    auto returnType = method->GetReturnType();
    if (returnType == nullptr)
    {
        method->Invoke(args);
        return 0;
    }
    else
    {
        Any result = method->Invoke(args);
        if (returnType == TypeMetaOf<int>())
        {
            lua_pushinteger(L, result.as<int>());
        }
        else if (returnType == TypeMetaOf<float>())
        {
            lua_pushnumber(L, result.as<float>());
        }
        else if (returnType == TypeMetaOf<char*>())
        {
            lua_pushstring(L, result.as<char*>());
        }
        else
        {
            *(void**)lua_newuserdata(L, sizeof(void*)) = result;
            luaL_getmetatable(L, returnType->name.c_str());
            lua_setmetatable(L, -2);
        }

        return 1;
    }
}

void LuaBinder::Bind(Meta* meta)
{
    for (auto& typeMeta : meta->types)
    {
        if (typeMeta->isClass())
        {
            auto classMeta = static_cast<IClassMeta*>(typeMeta);
            BindClass(classMeta);
        }
    }
}

void LuaBinder::BindClass(IClassMeta* classMeta)
{
    auto className = classMeta->name.c_str();

    luaL_newmetatable(L, className); // (1)

    for (auto constructor : classMeta->constructors)
    {
        int argCount = constructor->GetArgCount();
        std::string name = "constructor" + std::to_string(argCount);
        BindFunctionHelper(constructor, name);
    }

    for (auto& pair : classMeta->methods)
    {
        auto method = pair.second;
        BindFunctionHelper(method, method->name);
    }

    for (auto& pair : classMeta->functions)
    {
        auto function = pair.second;
        BindFunctionHelper(function, function->name);
    }

    // fields
//    {
//        lua_newtable(L); // set table (2)

//        for (auto field : type->fields)
//        {
//            *(IFieldMeta**)lua_newuserdata(L, size) = field;

//        }

//        lua_setfield(L, 1, "__newindex");
//    }

    //
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_setglobal(L, className);
}

void LuaBinder::BindFunctionHelper(IFunctionMeta* function, std::string name)
{
    *(IFunctionMeta**)lua_newuserdata(L, sizeof(void*)) = function;
    lua_pushcclosure(L, FunctionInvoker, 1);
    lua_setfield(L, -2, name.c_str());
}
