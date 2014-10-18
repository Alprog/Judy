
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

int SubStruct_Constructor(lua_State* L)
{
    auto size = sizeof(SubStruct*);
    auto udata = (SubStruct**)lua_newuserdata(L, size);

    *udata = new SubStruct();

    luaL_getmetatable(L, "SubStruct");
    lua_setmetatable(L, -2);

    return 1;
}

SubStruct* CheckSubStruct(lua_State* L, int n)
{
    return *(SubStruct**)luaL_checkudata(L, n, "SubStruct");
}

int SubStruct_GetE(lua_State* L)
{
    SubStruct* obj = CheckSubStruct(L, 1);
    lua_pushnumber(L, obj->e);
    return 1;
}

int SubStruct_SetE(lua_State* L)
{
    SubStruct* obj = CheckSubStruct(L, 1);
    int value = (int)luaL_checknumber(L, 2);
    obj->e = value;
    return 0;
}

void LuaBinder::Bind(Meta* meta)
{
    luaL_newmetatable(L, "SubStruct");      // metatable

    luaL_Reg reg[] =
    {
        { "new", SubStruct_Constructor },
        { "get_e", SubStruct_GetE },
        { "set_e", SubStruct_SetE },
        { NULL, NULL }
    };

    luaL_setfuncs(L, reg, 0);

    //lua_pushvalue(L, -1);                   // metatable | metatable
    //lua_setfield(L, -2, "__index");         // metatable

    lua_setglobal(L, "SubStruct");          // …

    //lua_pop(L, 1);

    /*for (auto type : meta->Types)
    {
        printf("%i\n", lua_gettop(L));

        luaL_newmetatable(L, type->name);

        lua_setfield(L, -1, "__index");

        printf("%s\n", type->name);
        printf("%i\n", lua_gettop(L));

        for (auto field : type->fields)
        {
            //field->name
        }
    }*/
}
