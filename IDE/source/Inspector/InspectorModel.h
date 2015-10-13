
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

    virtual int rowCount(const QModelIndex& index) const override;
    virtual int columnCount(const QModelIndex& index) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex& index) const override;
    virtual QModelIndex parent(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

private:
    inline InspectorItem* GetBaseItem(const QModelIndex& index) const;
    InspectorItem* GetSubItem(const QModelIndex& index) const;

    InspectorItem* rootItem;
};
