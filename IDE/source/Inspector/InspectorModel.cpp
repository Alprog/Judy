
#include "InspectorModel.h"
#include "Meta/Meta.h"
#include "Meta/ITypeMeta.h"
#include "Meta/IFieldMeta.h"
#include "Meta/PropertyMeta.h"
#include "Node.h"
#include "InspectorItem.h"

enum ColumnType
{
    Name = 0,
    Value = 1
};

InspectorModel::InspectorModel(Node* node)
{
    rootItem = new InspectorItem(node);
}

InspectorModel::~InspectorModel()
{
    delete rootItem;
}

int InspectorModel::rowCount(const QModelIndex &parent) const
{
    return rootItem->fields->size();
}

int InspectorModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant InspectorModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto item = rootItem;

    if (row < 0 || row >= item->fields->size()) { return QVariant(); }

    if (col == ColumnType::Name)
    {
        auto name = item->fields->at(row)->name;
        return QString::fromStdString(name);
    }
    else if (col == ColumnType::Value)
    {
        return QVariant();
    }

    return QVariant();
}
