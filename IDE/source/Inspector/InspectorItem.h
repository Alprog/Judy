
#pragma once

#include "Containers/List.h"
#include "Meta/Any.h"

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
    Any localData;
    Any pointer;
    int row;
    InspectorItem* parent;

    List<IFieldMeta*>* fields;
    List<InspectorItem*> childs;
};
