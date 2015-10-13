
#pragma once

#include <QAbstractTableModel>
#include "Containers/Map.h"
#include "Containers/List.h"

class Node;
class ITypeMeta;
class IFieldMeta;
class InspectorItem;

class InspectorModel : public QAbstractTableModel
{
public:
    InspectorModel(Node* node);
    ~InspectorModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    InspectorItem* rootItem;
};
