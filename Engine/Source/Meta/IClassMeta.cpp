
#include "IClassMeta.h"
#include "IFieldMeta.h"
#include "PropertyMeta.h"
#include "Containers/List.h"

::List<IFieldMeta*> IClassMeta::GetFieldsWithAttribute(std::string attribute, bool includeProperties)
{
    ::List<IFieldMeta*> list;

    for (auto& pair : fields)
    {
        auto fieldMeta = pair.second;
        if (fieldMeta->HasAttribute("Inspect"))
        {
            list.push_back(fieldMeta);
        }
    }

    if (includeProperties)
    {
        for (auto& pair : properties)
        {
            auto propertyMeta = pair.second;
            if (propertyMeta->HasAttribute("Inspect"))
            {
                list.push_back(propertyMeta);
            }
        }
    }

    return list;
}
