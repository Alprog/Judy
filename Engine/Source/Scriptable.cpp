
#include "Scriptable.h"

#include "LuaMachine.h"

Scriptable::Scriptable()
    : luaObject { nullptr }
{

}

Scriptable::~Scriptable()
{
    if (luaObject != nullptr)
    {
        LuaMachine::Instance()->UnregUserdata(this);
    }
}
