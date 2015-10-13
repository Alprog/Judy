
#include "PropertyMeta.h"

PropertyMeta::PropertyMeta(std::string name)
    : getter{nullptr}
    , setter{nullptr}
{
    this->name = name;
}

void PropertyMeta::Set(Any& object, Any& value)
{

}

Any PropertyMeta::Get(Any& object)
{
    return Any::empty;
}

Any PropertyMeta::GetAddr(Any& object)
{
    return Any::empty;
}

ITypeMeta* const PropertyMeta::GetType()
{
    if (getter != nullptr)
    {
        return getter->GetReturnType();
    }
    else if (setter != nullptr)
    {
        return setter->GetArgTypes()[0];
    }
    else
    {
        return nullptr;
    }
}
