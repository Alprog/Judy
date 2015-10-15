
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "ITypeMeta.h"
#include "Lua.h"

const char* UserdataTable = "UDATA";

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

        auto data = (void**)lua_newuserdata(L, sizeof(void*)); // TU
        *data = pointer;

        // set metatable (todo: rtti for actual type)
        luaL_getmetatable(L, type->name.c_str()); // TUM
        lua_setmetatable(L, -2); // TU

        lua_pushlightuserdata(L, pointer); // TUL
        lua_pushvalue(L, -2); // TULU
        lua_settable(L, -4); // TU
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
    auto field = *(IFieldMeta**)lua_touserdata(L, lua_upvalueindex(1));
    void* object = *(void**)lua_touserdata(L, 1);
    //Any result = field->get(object);
    //ProcessResult(L, result, field->GetType());
    return 1;
}

int FunctionInvoker(lua_State* L)
{
    auto function = *(IFunctionMeta**)lua_touserdata(L, lua_upvalueindex(1));

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
    auto function = *(IFunctionMeta**)lua_touserdata(L, lua_upvalueindex(1));

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
    lua_newtable(L);
    lua_setfield(L, LUA_REGISTRYINDEX, UserdataTable);

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

    luaL_newmetatable(L, className); // (1)

    for (auto constructor : classMeta->constructors)
    {
        int argCount = constructor->GetArgCount();
        std::string name = "new" + std::to_string(argCount);
        BindHelper(constructor, name, NewInvoker);
    }

    for (auto& pair : classMeta->methods)
    {
        auto method = pair.second;
        BindHelper(method, method->name, FunctionInvoker);
    }

    for (auto& pair : classMeta->functions)
    {
        auto function = pair.second;
        BindHelper(function, function->name, FunctionInvoker);
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

void LuaBinder::BindHelper(IFunctionMeta* function, std::string name, luaClosure closure)
{
    *(void**)lua_newuserdata(L, sizeof(void*)) = function;
    lua_pushcclosure(L, closure, 1);
    lua_setfield(L, -2, name.c_str());
}
