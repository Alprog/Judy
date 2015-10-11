
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
    , fields{nullptr}
{
    auto index = std::type_index(typeid(*node));
    auto typeMeta = Meta::Instance()->Find(index);
    fields = GetFields(typeMeta);

}

List<IFieldMeta*>* NodeInspectorModel::GetFields(ITypeMeta* typeMeta)
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

int NodeInspectorModel::rowCount(const QModelIndex &parent) const
{
    return fields ? fields->size() : 0;
}

int NodeInspectorModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant NodeInspectorModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    auto col = index.column();


    if (row < 0 || row >= fields->size()) { return QVariant(); }

    if (col == ColumnType::Name)
    {
        auto name = fields->at(row)->name;
        return QString::fromStdString(name);
    }
    else if (col == ColumnType::Value)
    {
        return QVariant();
    }

    return QVariant();
}
