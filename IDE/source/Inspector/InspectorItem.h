
#pragma once

#include "Containers/List.h"
#include "Meta/Any.h"

class ITypeMeta;
class IFieldMeta;
class Node;

class InspectorItem
{
public:
    InspectorItem(Node* node);
    InspectorItem(Any& pointer, IFieldMeta* field, InspectorItem* parent, int row);
    ~InspectorItem();

    InspectorItem* GetParent();
    size_t GetChildCount();
    InspectorItem* GetChild(size_t index);
    std::string GetName();

private:
    static List<IFieldMeta*>* GetFields(ITypeMeta* typeMeta);

public:
    Any localData;
    Any pointer;

    int row;
    InspectorItem* parent;

    IFieldMeta* field;
    List<InspectorItem*> childs;
};
