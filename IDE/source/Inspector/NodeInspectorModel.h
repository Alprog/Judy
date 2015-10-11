
#pragma once

#include <QAbstractTableModel>
#include "Containers/Map.h"
#include "Containers/List.h"

class Node;
class ITypeMeta;

class NodeInspectorModel : public QAbstractTableModel
{
public:
    NodeInspectorModel(Node* node);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    static List<IPropertyMeta*>* GetProperties(ITypeMeta* typeMeta);

private:
    Node* node;
    List<IPropertyMeta*>* properties;
};
