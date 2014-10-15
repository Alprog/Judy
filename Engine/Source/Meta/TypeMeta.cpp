
#include "TypeMeta.h"

void TypeMeta::set(void* object, char* name, void* value)
{
    for (auto field : fields)
    {
        if (field->name == name)
        {
            field->set(object, value);
        }
    }
}

void* TypeMeta::get(void* object, char* name)
{
    for (auto field : fields)
    {
        if (field->name == name)
        {
            return field->get(object);
        }
    }
    return 0;
}

Variant TypeMeta::invoke(void* object, char* name, std::vector<Variant> args)
{
    for (auto method : methods)
    {
        if (method->name == name)
        {
            return method->Invoke(object, args);
        }
    }
}
