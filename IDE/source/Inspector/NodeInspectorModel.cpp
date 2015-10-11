
#include "NodeInspectorModel.h"
#include <typeindex>
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IFieldMeta.h"
#include "Meta/PropertyMeta.h"
#include "Node.h"

enum ColumnType
{
    Name = 0,
    Value = 1
};

NodeInspectorModel::NodeInspectorModel(Node* node)
    : node{node}
    , properties{nullptr}
{
    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::Instance()->Find(index);
    properties = GetProperties(typeMeta);

}

List<IFieldMeta*>* NodeInspectorModel::GetProperties(ITypeMeta* typeMeta)
{
    static Map<ITypeMeta*, List<IFieldMeta*>> cache;

    auto it = cache.find(typeMeta);
    if (it != std::end(cache))
    {
        return &it->second;
    }

    auto& properties = cache[typeMeta] = List<IFieldMeta*>(); // cache list

    if (typeMeta->isClass())
    {
        auto classMeta = static_cast<IClassMeta*>(typeMeta);

        // base properties
        for (auto& baseMeta : classMeta->baseTypes)
        {
            for (auto& property : GetProperties(baseMeta))
            {
                properties.push_back(property);
            }
        }

        // properties
        for (auto& pair : classMeta->properties)
        {
            auto fieldInfo = pair.second;
            if (fieldInfo->HasAttribute("Inspect"))
            {
                properties.push_back(fieldInfo);
            }
        }

        // fields
        for (auto& pair : classMeta->fields)
        {
            auto fieldInfo = pair.second;
            if (fieldInfo->HasAttribute("Inspect"))
            {
                properties.push_back(fieldInfo);
            }
        }
    }

    return &properties;
}

int NodeInspectorModel::rowCount(const QModelIndex &parent) const
{
    return properties ? properties->size() : 0;
}

int NodeInspectorModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant NodeInspectorModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    auto col = index.column();


    if (row < 0 || row >= properties->size()) { return QVariant(); }

    if (col == ColumnType::Name)
    {
        auto name = properties->at(row)->name;
        return QString::fromStdString(name);
    }
    else if (col == ColumnType::Value)
    {
        return QVariant();
    }

    return QVariant();
}
