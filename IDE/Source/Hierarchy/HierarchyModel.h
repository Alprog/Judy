
#pragma once

#include <qabstractitemmodel.h>

class Node;

class HierarchyModel : public QAbstractItemModel
{
public:
    HierarchyModel();
    void setNode(Node* node);

    virtual int rowCount(const QModelIndex& index) const override;
    virtual int columnCount(const QModelIndex& index) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex& index) const override;
    virtual QModelIndex parent(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

    Node* getNode(const QModelIndex& index) const;

private:
    Node* rootNode;
};
