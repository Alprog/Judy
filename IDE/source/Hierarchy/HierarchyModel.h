
#pragma once

#include <QAbstractItemModel.h>

class Node;

class HierarchyModel : public QAbstractItemModel
{
public:
    HierarchyModel();
    void SetNode(Node* node);

    virtual int rowCount(const QModelIndex& index) const override;
    virtual int columnCount(const QModelIndex& index) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex& index) const override;
    virtual QModelIndex parent(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

private:
    Node* GetNode(const QModelIndex& index) const;

    Node* rootNode;
};
