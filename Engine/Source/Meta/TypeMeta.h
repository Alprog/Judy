
#pragma once

#include "Variant.h"

#include "FieldMeta.h"
#include "MethodMeta.h"

#include <vector>

class TypeMeta
{
public:
    void set(void* object, char* name, void* value);
    void* get(void* object, char* name);

    Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<FieldMeta*> fields;
    std::vector<MethodMeta*> methods;
};

template <typename ClassType>
class ClassMeta : public TypeMeta
{
public:
    static ClassMeta* Instance()
    {
        static ClassMeta<ClassType> instance;
        return &instance;
    }

    void* create()
    {
        return new ClassType();
    }
};
