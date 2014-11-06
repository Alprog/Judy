
#include "Binder.h"

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"

#include "App.h"

LuaBinder::LuaBinder(lua_State* L)
    : L { L }
{
}

template <typename T>
T* CheckType(lua_State* L, int n)
{
    char* name = TypeMeta<T>::Instance()->name;
    return *(T**)luaL_checkudata(L, n, name);
}

int SubStruct_Constructor(lua_State* L)
{
    auto size = sizeof(SubStruct*);
    auto udata = (SubStruct**)lua_newuserdata(L, size);

    *udata = new SubStruct();

    luaL_getmetatable(L, "SubStruct");
    lua_setmetatable(L, -2);

    return 1;
}

int TestStruct_Constructor(lua_State* L)
{
    auto size = sizeof(TestStruct*);
    auto udata = (TestStruct**)lua_newuserdata(L, size);

    auto a = (int)luaL_checknumber(L, 1);
    auto b = (int)luaL_checknumber(L, 2);
    auto c = (char*)luaL_checkstring(L, 3);
    auto d = *CheckType<SubStruct>(L, 4);

    *udata = new TestStruct(a, b, c, d);

    luaL_getmetatable(L, "TestStruct");
    lua_setmetatable(L, -2);

    return 1;
}

int SubStruct_GetE(lua_State* L)
{
    SubStruct* obj = CheckType<SubStruct>(L, 1);
    lua_pushnumber(L, obj->e);
    return 1;
}

int SubStruct_SetE(lua_State* L)
{
    SubStruct* obj = CheckType<SubStruct>(L, 1);
    int value = (int)luaL_checknumber(L, 2);
    obj->e = value;
    return 0;
}

int TestStruct_GetD(lua_State* L)
{
    TestStruct* obj = CheckType<TestStruct>(L, 1);

    auto size = sizeof(SubStruct*);
    auto udata = (SubStruct**)lua_newuserdata(L, size);
    *udata = &obj->d;

    luaL_getmetatable(L, "SubStruct");
    lua_setmetatable(L, -2);

    return 1;
}

int TestStruct_SetD(lua_State* L)
{
    TestStruct* obj = CheckType<TestStruct>(L, 1);
    auto value = *CheckType<SubStruct>(L, 2);
    obj->d = value;
    return 0;
}

template <typename ClassType, typename FieldType>
int Setter(lua_State* L)
{
    auto object = CheckType<ClassType>(L, 1);
    auto value = CheckType<FieldType>(L, 2);

    IFieldMeta* meta;
    meta->set(object, value);

    return 0;
}

template <typename Type>
int Constructor(lua_State* L)
{
    auto size = sizeof(Type*);
    *(Type**)lua_newuserdata(L, size) = new Type();

    luaL_getmetatable(L, TypeMeta<Type>::Instance()->name);
    lua_setmetatable(L, -2);

    return 1;
}

int MethodInvoker(lua_State* L)
{
    auto method = *(IMethodMeta**)lua_touserdata(L, lua_upvalueindex(1));
    void* object = *(void**)lua_touserdata(L, 1);

    printf("%p \n", object);

    std::vector<Variant> args = {};

    auto returnType = method->GetReturnType();

    printf("%s \n", returnType->name);

    if (returnType == nullptr)
    {
        method->Invoke(object, args);
        return 0;
    }
    else
    {
        Variant result = method->Invoke(object, args);
        int a = result;
        lua_pushnumber(L, a);
        return 1;
    }
}

void LuaBinder::Bind(Meta* meta)
{
    luaL_newmetatable(L, "SubStruct");

    luaL_Reg reg[] =
    {
        { "new", SubStruct_Constructor },
        { "get_e", SubStruct_GetE },
        { "set_e", SubStruct_SetE },
        { NULL, NULL }
    };

    luaL_setfuncs(L, reg, 0);
    lua_setglobal(L, "SubStruct");

    //---------------------------------------

    luaL_newmetatable(L, "TestStruct");

    luaL_Reg reg2[] =
    {
        { "new", TestStruct_Constructor },
        { "get_d", TestStruct_GetD },
        { "set_d", TestStruct_SetD },
        { NULL, NULL }
    };

    luaL_setfuncs(L, reg2, 0);
    lua_setglobal(L, "TestStruct");


    ITypeMeta* type = TypeMeta<Node>::Instance();
    luaL_newmetatable(L, type->name);

    lua_pushcfunction(L, Constructor<Node>);
    lua_setfield(L, -2, "new");

    auto size = sizeof(IMethodMeta*);
    for (auto method : type->methods)
    {
        *(IMethodMeta**)lua_newuserdata(L, size) = method;
        lua_pushcclosure(L, MethodInvoker, 1);
        lua_setfield(L, -2, method->name);

        break;
    }

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_setglobal(L, type->name);

}
