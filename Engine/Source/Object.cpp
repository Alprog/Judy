
#include "Object.h"

#include "LuaMachine.h"
#include "luainc.h"

Object::Object()
    : referenceCount{0}
    , luaObject{nullptr}
{

}

Object::~Object()
{
}

void Object::retain()
{
    referenceCount++;
    printf("inc %i %p\n", referenceCount, this);
    fflush(stdout);
}

void Object::release()
{
    referenceCount--;
    printf("dec %i %p\n", referenceCount, this);
    fflush(stdout);
    if (referenceCount == 0)
    {
        if (luaObject == nullptr)
        {
            delete this;
        }
        else
        {
            // ensure that we don't keep luaObject manualy
            LuaMachine::instance()->releaseUserdata(luaObject);
            // and wait when it garbage collected
        }
    }
}

bool lua_isemptytable(lua_State* L, int index)
{
    lua_pushnil(L);
    if (lua_next(L, index - 1))
    {
        lua_pop(L, 2);
        return false;
    }
    return true;
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
        bool keepUserdata = true;
        if (object->luaClass.empty())
        {
            lua_getuservalue(L, -1); // UT
            keepUserdata = !lua_isemptytable(L, -1);
            lua_pop(L, 1); // U
        }

        if (keepUserdata)
        {
            // force keep userdata reference
            LuaMachine::instance()->retainUserdata(object->luaObject);

            // mark for finalization again
            lua_getmetatable(L, -1); // UM
            lua_setmetatable(L, -2); // U
        }
        else
        {
            // delete lua object
            object->luaObject = nullptr;
        }

        lua_pop(L, 1);
    }

    return 0;
}
