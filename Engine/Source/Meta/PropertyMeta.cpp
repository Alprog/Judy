
#include "PropertyMeta.h"

PropertyMeta::PropertyMeta(std::string name)
    : getter{nullptr}
    , setter{nullptr}
{
    this->name = name;
}

void PropertyMeta::set(Any& object, Any& value)
{
    std::vector<Any> args {object, value};
    setter->invoke(args);
}

Any PropertyMeta::get(Any& object)
{
    return getter->invoke(object);
}

Any PropertyMeta::getAddr(Any& object)
{
    return Any::empty;
}

ITypeMeta* const PropertyMeta::getType()
{
    if (getter != nullptr)
    {
        return getter->getReturnType();
    }
    else if (setter != nullptr)
    {
        return setter->getArgTypes()[0];
    }
    else
    {
        return nullptr;
    }
}
