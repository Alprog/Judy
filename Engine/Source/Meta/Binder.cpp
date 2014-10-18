
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

void LuaBinder::Bind(Meta* meta)
{
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
