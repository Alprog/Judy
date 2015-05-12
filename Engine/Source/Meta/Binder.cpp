
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"

#include "App.h"

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
    ClassMetaBase* type = (ClassMetaBase*)TypeMetaOf<Node>();

    luaL_newmetatable(L, type->name.c_str()); // (1)

    auto size = sizeof(void*);

    for (auto constructor : type->constructors)
    {
        int argCount = constructor->GetArgCount();
        *(IFunctionMeta**)lua_newuserdata(L, size) = constructor;
        lua_pushcclosure(L, FunctionInvoker, 1);
        std::string text = "constructor" + std::to_string(argCount);
        lua_setfield(L, 1, text.c_str());
    }

    for (auto method : type->methods)
    {
        *(IFunctionMeta**)lua_newuserdata(L, size) = method;
        lua_pushcclosure(L, FunctionInvoker, 1);
        lua_setfield(L, 1, method->name);
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

    lua_pushvalue(L, 1);
    lua_setfield(L, 1, "__index");

    lua_setglobal(L, "Node");
    printf("NAME: %s \n", type->name.c_str());
}
