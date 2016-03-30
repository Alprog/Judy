
#include "IMemberMeta.h"

bool IMemberMeta::HasAttribute(std::string name)
{
    return attributes.find(name) != std::end(attributes);
}
