
#include "PropertyMeta.h"

PropertyMeta::PropertyMeta(std::string name)
    : getter{nullptr}
    , setter{nullptr}
{
    this->name = name;
}
