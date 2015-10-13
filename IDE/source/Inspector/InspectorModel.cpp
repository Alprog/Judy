
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
    return GetItem(parent)->GetChildCount();
}

int InspectorModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

InspectorItem* InspectorModel::GetItem(const QModelIndex& index) const
{
    if (index.isValid())
    {
        auto pointer = index.internalPointer();
        return static_cast<InspectorItem*>(pointer);
    }
    else
    {
        return rootItem;
    }
}

QModelIndex InspectorModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    auto parentItem = GetItem(parent);
    auto item = parentItem->GetChild(row);

    if (item)
    {
        return createIndex(row, column, item);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex InspectorModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) { return QModelIndex(); }

    auto item = GetItem(index);

    auto parent = item->GetParent();
    if (parent == nullptr || parent == rootItem)
    {
        return QModelIndex();
    }
    else
    {
        return createIndex(parent->row, 0, parent);
    }
}

QVariant InspectorModel::data(const QModelIndex &index, int role) const
{
    auto col = index.column();

    auto item = GetItem(index);

    if (col == ColumnType::Name)
    {
        auto name = item->GetName();
        return QString::fromStdString(name);
    }
    else if (col == ColumnType::Value)
    {
        return QVariant();
    }

    return QVariant();
}
