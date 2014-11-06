
#pragma once

#include "Variant.h"

#include "FieldMeta.h"
#include "MethodMeta.h"
#include "MetaDefiner.h"

#include <vector>

class ITypeMeta
{
public:
    char* name;

    void set(void* object, char* name, void* value);
    void* get(void* object, char* name);

    Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;

    virtual Variant DefaultConstructor() = 0;
};

template <typename ClassType>
class TypeMeta : public ITypeMeta
{
public:
    static TypeMeta* Instance()
    {
        static TypeMeta<ClassType> instance;
        return &instance;
    }

    Variant DefaultConstructor() override
    {
        return Constructor();
    }

    template <typename... Types>
    Variant Constructor()
    {
        return ClassType(Types...);
    }
};
