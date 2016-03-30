
#include "InspectorItem.h"
#include "Node.h"
#include <typeindex>
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IClassMeta.h"
#include "Meta/IFieldMeta.h"
#include "Meta/PropertyMeta.h"
#include "Containers/Map.h"

InspectorItem* InspectorItem::Create(Node* node)
{
    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::Instance()->Find(index);
    auto fields = GetFields(typeMeta);
    return new InspectorItem(node, fields, nullptr, 0);
}

InspectorItem::InspectorItem(Any pointer, List<IFieldMeta*>* fields, InspectorItem* parent, int row)
    : pointer{pointer}
    , fields{fields}
    , parent{parent}
    , row{row}
{
    for (auto i = 0; i < fields->size(); i++)
    {
        InspectorItem* child = nullptr;

        auto field = fields->at(i);
        auto type = field->GetType();
        auto subFields = GetFields(type);
        if (subFields->size() > 0)
        {
            bool isProperty = dynamic_cast<PropertyMeta*>(field);
            if (!isProperty)
            {
                auto subPointer = field->GetAddr(pointer);
                child = new InspectorItem(subPointer, subFields, this, i);
            }
        }

        childs.push_back(child);
    }
}

InspectorItem::~InspectorItem()
{
    for (auto& child : childs)
    {
        if (child != nullptr)
        {
            delete child;
        }
    }
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

QVariant InspectorItem::GetName(int i)
{
    auto field = fields->at(i);
    return QString::fromStdString(field->name);
}

QVariant InspectorItem::GetValue(int i)
{
    auto field = fields->at(i);

    if (field->GetType() == TypeMetaOf<std::string>())
    {
        auto text = field->Get(pointer).as<std::string>();
        return QString::fromStdString(text);
    }
    else if (field->GetType() == TypeMetaOf<Vector3>())
    {
        auto vector = field->Get(pointer).as<Vector3>();
        auto text = std::to_string(vector.x) + "; " + std::to_string(vector.y) + "; " + std::to_string(vector.z);
        return QString::fromStdString(text);
    }
    else if (field->GetType() == TypeMetaOf<float>())
    {
        return field->Get(pointer).as<float>();
    }

    return QVariant();
}

bool InspectorItem::SetValue(int i, const QVariant& value)
{
    auto field = fields->at(i);

    if (field->GetType() == TypeMetaOf<float>())
    {
        Any any = value.toFloat();
        field->Set(pointer, any);
        return true;
    }

    return false;
}
