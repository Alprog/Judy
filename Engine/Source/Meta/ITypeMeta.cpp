
#include "ITypeMeta.h"
//#include "FieldMeta.h"
//#include "MethodMeta.h"

ITypeMeta::ITypeMeta()
    : isClass {false}
{
}

/*void ITypeMeta::set(void* object, char* name, void* value)
{
    for (auto field : fields)
    {
        if (field->name == name)
        {
            field->set(object, value);
        }
    }
}

void* ITypeMeta::get(void* object, char* name)
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

Variant ITypeMeta::invoke(void* object, char* name, std::vector<Variant> args)
{
    for (auto method : methods)
    {
        if (method->name == name)
        {
            return Variant::empty; //method->Invoke(object, args);
        }
    }
}*/
