
#pragma once

#include <QAbstractItemModel>
#include "Containers/Map.h"
#include "Containers/List.h"

class Node;
class ITypeMeta;
class IFieldMeta;
class InspectorItem;

class InspectorModel : public QAbstractItemModel
{
public:
    InspectorModel(Node* node);
    ~InspectorModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    InspectorItem* GetItem(const QModelIndex& index) const;

    InspectorItem* rootItem;
};
