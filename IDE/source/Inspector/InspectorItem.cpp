
#include "InspectorItem.h"
#include "Node.h"
#include <typeindex>
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IClassMeta.h"
#include "Meta/IFieldMeta.h"
#include "Containers/Map.h"

InspectorItem::InspectorItem(Node* node)
    : parent{nullptr}
{
    pointer = node;

    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::Instance()->Find(index);

    auto fields = GetFields(typeMeta);
    for (auto row = 0; row < fields->size(); row++)
    {
        auto item = new InspectorItem(pointer, fields->at(row), this, row);
        childs.push_back(item);
    }
}

InspectorItem::InspectorItem(Any& pointer, IFieldMeta* field, InspectorItem* parent, int row)
{
    this->pointer = pointer;
    this->field = field;
    this->parent = parent;
    this->row = row;

    auto typeMeta = field->GetType();
    auto fields = GetFields(typeMeta);
    for (auto row = 0; row < fields->size(); row++)
    {
        auto item = new InspectorItem(pointer, fields->at(row), this, row);
        childs.push_back(item);
    }
}

InspectorItem::~InspectorItem()
{
    for (auto& child : childs)
    {
        delete child;
    }
}

InspectorItem* InspectorItem::GetParent()
{
    return parent;
}

size_t InspectorItem::GetChildCount()
{
    return childs.size();
}

InspectorItem* InspectorItem::GetChild(size_t index)
{
    return childs[index];
}

std::string InspectorItem::GetName()
{
    return field->name;
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
