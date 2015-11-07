
#include "Object.h"

#include "LuaMachine.h"

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
    if (referenceCount == 1 && luaObject != nullptr)
    {
        //LuaMachine::Instance()->RetainUserdata(this);
    }
}

void Object::Release()
{
    referenceCount--;
    if (referenceCount == 0)
    {
        if (luaObject == nullptr)
        {
            delete this;
        }
        else
        {
            //LuaMachine::Instance()->ReleaseUserdata(this);
        }
    }
}
