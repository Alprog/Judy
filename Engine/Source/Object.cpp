
#include "Object.h"

#include "LuaMachine.h"
#include "Lua.h"

Object::Object()
    : referenceCount{0}
    , luaObject{nullptr}
{

}

Object::~Object()
{
}

void Object::Retain()
{
    referenceCount++;
    printf("inc %i %p\n", referenceCount, this);
}

void Object::Release()
{
    referenceCount--;
    printf("dec %i %p\n", referenceCount, this);
    if (referenceCount == 0)
    {
        if (luaObject == nullptr)
        {
            delete this;
        }
        else
        {
            // ensure that we don't keep luaObject manualy
            LuaMachine::Instance()->ReleaseUserdata(luaObject);
            // and wait when it garbage collected
        }
    }
}

int Object::GC(lua_State* L)
{
    // U
    lua_pushvalue(L, -1); // UU
    Object* object = *(Object**)lua_touserdata(L, -1); // U

    if (object->referenceCount == 0)
    {
        // delete cpp and lua object
        delete object;
        lua_pop(L, 1);
    }
    else
    {
        lua_getuservalue(L, -1); // UT
        if (lua_isemptytable(L, -1))
        {
            // delete lua object
            object->luaObject = nullptr;
            lua_pop(L, 2);
        }
        else
        {
            // force keep userdata reference
            LuaMachine::Instance()->RetainUserdata(object->luaObject);

            // mark for finalization again
            lua_getmetatable(L, -1); // UM
            lua_setmetatable(L, -2); // U
        }
    }

    return 0;
}
