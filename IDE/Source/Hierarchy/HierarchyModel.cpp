
#include "HierarchyModel.h"
#include "Node.h"

HierarchyModel::HierarchyModel()
    : rootNode{nullptr}
{
}

void HierarchyModel::setNode(Node* node)
{
    rootNode = node;
}

Node* HierarchyModel::getNode(const QModelIndex& index) const
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
    auto node = getNode(index);
    return node ? node->childCount() : 0;
}

int HierarchyModel::columnCount(const QModelIndex& index) const
{
    return 1;
}

QModelIndex HierarchyModel::index(int row, int column, const QModelIndex& index) const
{
    auto node = getNode(index);
    if (node != nullptr)
    {
        return createIndex(row, column, node->child(row));
    }
    return QModelIndex(); // invalid
}

QModelIndex HierarchyModel::parent(const QModelIndex& index) const
{
    auto node = getNode(index);
    if (node != rootNode)
    {
        auto parent = node->getParent();
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
        auto node = getNode(index);
        return QString::fromStdString("Node");
    }

    return QVariant();
}
