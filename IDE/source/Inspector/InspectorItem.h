
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

private:
    static List<IFieldMeta*>* GetFields(ITypeMeta* typeMeta);

public:
    Any localData;
    Any pointer;
    List<IFieldMeta*>* fields;
};
