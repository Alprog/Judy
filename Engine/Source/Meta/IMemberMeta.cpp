
#include "IMemberMeta.h"

bool IMemberMeta::hasAttribute(std::string name)
{
    return attributes.find(name) != std::end(attributes);
}
