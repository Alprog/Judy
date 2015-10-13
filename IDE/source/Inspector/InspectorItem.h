
#pragma once

#include "Containers/List.h"

class ITypeMeta;
class IFieldMeta;

struct InspectorItem
{

    void* data;
    List<IFieldMeta*>* fields;

    static List<IFieldMeta*>* GetFields(ITypeMeta* typeMeta);
};
