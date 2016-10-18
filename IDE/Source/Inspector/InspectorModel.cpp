
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
    rootItem = InspectorItem::create(node);
}

InspectorModel::~InspectorModel()
{
    delete rootItem;
}

InspectorItem* InspectorModel::getBaseItem(const QModelIndex& index) const
{
    return static_cast<InspectorItem*>(index.internalPointer());
}

InspectorItem* InspectorModel::getSubItem(const QModelIndex& index) const
{
    auto baseItem = getBaseItem(index);
    if (baseItem == nullptr)
    {
        return rootItem;
    }
    else
    {
        return baseItem->getChild(index.row());
    }
}

int InspectorModel::rowCount(const QModelIndex& index) const
{
    auto subItem = getSubItem(index);
    return subItem ? subItem->getChildCount() : 0;
}

int InspectorModel::columnCount(const QModelIndex& index) const
{
    return 2;
}

QModelIndex InspectorModel::index(int row, int column, const QModelIndex& index) const
{
    auto subItem = getSubItem(index);
    if (subItem)
    {
        return createIndex(row, column, subItem);
    }
    return QModelIndex(); // invalid
}

QModelIndex InspectorModel::parent(const QModelIndex& index) const
{
    auto baseItem = getBaseItem(index);

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
        return createIndex(baseItem->getRow(), 0, baseItem->getParent());
    }
}

QVariant InspectorModel::data(const QModelIndex& index, int role) const
{
    auto item = getBaseItem(index);

    if (role == Qt::DisplayRole)
    {
        auto row = index.row();
        auto col = index.column();
        if (col == ColumnType::Name)
        {
            return item->getName(row);
        }
        else if (col == ColumnType::Value)
        {
            return item->getValue(row);
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

    auto item = getBaseItem(index);
    if (role == Qt::EditRole)
    {
        return item->setValue(index.row(), value);
    }
    return false;
}
