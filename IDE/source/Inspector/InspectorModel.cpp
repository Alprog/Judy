
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
        return baseItem->childs[index.row()];
    }
}

int InspectorModel::rowCount(const QModelIndex& index) const
{
    auto subItem = GetSubItem(index);
    return subItem ? subItem->fields->size() : 0;
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
        return createIndex(baseItem->row, 0, baseItem->parent);
    }
}

QVariant InspectorModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto item = GetBaseItem(index);

    auto field = item->fields->at(row);

    if (col == ColumnType::Name)
    {
        return QString::fromStdString(field->name);
    }
    else if (col == ColumnType::Value)
    {
        return QVariant();
    }

    return QVariant();
}
