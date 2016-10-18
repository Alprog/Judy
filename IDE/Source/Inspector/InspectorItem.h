
#pragma once

#include "Containers/List.h"
#include "Meta/Any.h"
#include <QVariant>

class ITypeMeta;
class IFieldMeta;
class Node;

class InspectorItem
{
public:
    static InspectorItem* create(Node* node);
    InspectorItem(Any pointer, List<IFieldMeta*>* fields, InspectorItem* parent, int row);
    ~InspectorItem();

private:
    static List<IFieldMeta*>* getFields(ITypeMeta* typeMeta);

public:
    QVariant getName(int i);
    QVariant getValue(int i);
    bool setValue(int i, const QVariant& value);

    inline size_t getChildCount() const { return childs.size(); }
    inline InspectorItem* getChild(size_t i) const { return childs[i]; }
    inline InspectorItem* getParent() const { return parent; }
    inline int getRow() const { return row; }

private:
    Any localData;
    Any pointer;
    List<InspectorItem*> childs;
    List<IFieldMeta*>* fields;
    int row;
    InspectorItem* parent;
};
