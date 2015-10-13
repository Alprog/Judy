
#include "HierarchyModel.h"
#include "Node.h"

HierarchyModel::HierarchyModel()
    : rootNode{nullptr}
{
}

void HierarchyModel::SetNode(Node* node)
{
    rootNode = node;
}

Node* HierarchyModel::GetNode(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return rootNode;
    }
    else
    {
        return static_cast<Node*>(index.internalPointer());
    }
}

int HierarchyModel::rowCount(const QModelIndex& index) const
{
    auto node = GetNode(index);
    return node ? node->ChildCount() : 0;
}

int HierarchyModel::columnCount(const QModelIndex& index) const
{
    return 1;
}

QModelIndex HierarchyModel::index(int row, int column, const QModelIndex& index) const
{
    auto node = GetNode(index);
    if (node != nullptr)
    {
        return createIndex(row, column, node->Child(row));
    }
    return QModelIndex(); // invalid
}

QModelIndex HierarchyModel::parent(const QModelIndex& index) const
{
    auto node = GetNode(index);
    if (node != rootNode)
    {
        auto parent = node->Parent();
        if (parent && parent != rootNode)
        {
            return createIndex(0, 0, parent);
        }
    }
    return QModelIndex();
}

QVariant HierarchyModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        auto node = GetNode(index);
        return QString::fromStdString("Node");
    }

    return QVariant();
}
