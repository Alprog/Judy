
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
    rootItem = InspectorItem::Create(node);
}

InspectorModel::~InspectorModel()
{
    delete rootItem;
}

InspectorItem* InspectorModel::GetBaseItem(const QModelIndex& index) const
{
    return static_cast<InspectorItem*>(index.internalPointer());
}

InspectorItem* InspectorModel::GetSubItem(const QModelIndex& index) const
{
    auto baseItem = GetBaseItem(index);
    if (baseItem == nullptr)
    {
        return rootItem;
    }
    else
    {
        return baseItem->GetChild(index.row());
    }
}

int InspectorModel::rowCount(const QModelIndex& index) const
{
    auto subItem = GetSubItem(index);
    return subItem ? subItem->GetChildCount() : 0;
}

int InspectorModel::columnCount(const QModelIndex& index) const
{
    return 2;
}

QModelIndex InspectorModel::index(int row, int column, const QModelIndex& index) const
{
    auto subItem = GetSubItem(index);
    if (subItem)
    {
        return createIndex(row, column, subItem);
    }
    return QModelIndex(); // invalid
}

QModelIndex InspectorModel::parent(const QModelIndex& index) const
{
    auto baseItem = GetBaseItem(index);

    if (baseItem == nullptr)
    {
        throw std::runtime_error("item hasn't parent");
    }

    if (baseItem == rootItem)
    {
        return QModelIndex();
    }
    else
    {
        return createIndex(baseItem->GetRow(), 0, baseItem->GetParent());
    }
}

QVariant InspectorModel::data(const QModelIndex& index, int role) const
{
    auto item = GetBaseItem(index);

    if (role == Qt::DisplayRole)
    {
        auto row = index.row();
        auto col = index.column();
        if (col == ColumnType::Name)
        {
            return item->GetName(row);
        }
        else if (col == ColumnType::Value)
        {
            return item->GetValue(row);
        }
    }

    return QVariant();
}

Qt::ItemFlags InspectorModel::flags(const QModelIndex& index) const
{
    auto flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    auto col = index.column();
    if (col == ColumnType::Value)
    {
        return flags | Qt::ItemIsEditable;
    }
    return flags;
}

bool InspectorModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.column() != ColumnType::Value) { return false; }

    auto item = GetBaseItem(index);
    if (role == Qt::EditRole)
    {
        return item->SetValue(index.row(), value);
    }
    return false;
}
