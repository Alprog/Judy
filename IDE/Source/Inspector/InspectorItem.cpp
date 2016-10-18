
#include "InspectorItem.h"
#include "Node.h"
#include <typeindex>
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IClassMeta.h"
#include "Meta/IFieldMeta.h"
#include "Meta/PropertyMeta.h"
#include "Containers/Map.h"

InspectorItem* InspectorItem::create(Node* node)
{
    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::instance()->find(index);
    auto fields = getFields(typeMeta);
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
        auto type = field->getType();
        auto subFields = getFields(type);
        if (subFields->size() > 0)
        {
            bool isProperty = dynamic_cast<PropertyMeta*>(field);
            if (!isProperty)
            {
                auto subPointer = field->getAddr(pointer);
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

List<IFieldMeta*>* InspectorItem::getFields(ITypeMeta* typeMeta)
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
            for (auto& field : getFields(baseMeta))
            {
                list.push_back(field);
            }
        }

        auto fields = classMeta->getFieldsWithAttribute("Inspect", true);
        for (auto& field : fields)
        {
            list.push_back(field);
        }
    }

    return &list;
}

QVariant InspectorItem::getName(int i)
{
    auto field = fields->at(i);
    return QString::fromStdString(field->name);
}

QVariant InspectorItem::getValue(int i)
{
    auto field = fields->at(i);

    if (field->getType() == typeMetaOf<std::string>())
    {
        auto text = field->get(pointer).as<std::string>();
        return QString::fromStdString(text);
    }
    else if (field->getType() == typeMetaOf<Vector3>())
    {
        auto vector = field->get(pointer).as<Vector3>();
        auto text = std::to_string(vector.x) + "; " + std::to_string(vector.y) + "; " + std::to_string(vector.z);
        return QString::fromStdString(text);
    }
    else if (field->getType() == typeMetaOf<float>())
    {
        return field->get(pointer).as<float>();
    }

    return QVariant();
}

bool InspectorItem::setValue(int i, const QVariant& value)
{
    auto field = fields->at(i);

    if (field->getType() == typeMetaOf<float>())
    {
        Any any = value.toFloat();
        field->set(pointer, any);
        return true;
    }

    return false;
}
