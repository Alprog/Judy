
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
    static InspectorItem* Create(Node* node);
    InspectorItem(Any pointer, List<IFieldMeta*>* fields, InspectorItem* parent, int row);
    ~InspectorItem();

private:
    static List<IFieldMeta*>* GetFields(ITypeMeta* typeMeta);

public:
    QVariant GetName(int i);
    QVariant GetValue(int i);

    inline size_t GetChildCount() const { return childs.size(); }
    inline InspectorItem* GetChild(size_t i) const { return childs[i]; }
    inline InspectorItem* GetParent() const { return parent; }
    inline int GetRow() const { return row; }

private:
    Any localData;
    Any pointer;
    List<InspectorItem*> childs;
    List<IFieldMeta*>* fields;
    int row;
    InspectorItem* parent;
};
