
#include "InspectorItem.h"
#include "Node.h"
#include <typeindex>
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IClassMeta.h"
#include "Meta/IFieldMeta.h"
#include "Containers/Map.h"

InspectorItem::InspectorItem(Node* node)
{
    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::Instance()->Find(index);
    fields = GetFields(typeMeta);
    pointer = node;
}

List<IFieldMeta*>* InspectorItem::GetFields(ITypeMeta* typeMeta)
{
    static Map<ITypeMeta*, List<IFieldMeta*>> cache;

    auto it = cache.find(typeMeta);
    if (it != std::end(cache))
    {
        return &it->second;
    }

    auto& list = cache[typeMeta] = List<IFieldMeta*>(); // cache list

    if (typeMeta->isClass())
    {
        auto classMeta = static_cast<IClassMeta*>(typeMeta);

        // base fields
        for (auto& baseMeta : classMeta->baseTypes)
        {
            for (auto& field : GetFields(baseMeta))
            {
                list.push_back(field);
            }
        }

        auto fields = classMeta->GetFieldsWithAttribute("Inspect", true);
        for (auto& field : fields)
        {
            list.push_back(field);
        }
    }

    return &list;
}
