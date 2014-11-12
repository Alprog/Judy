
#pragma once

#include <vector>
#include "Variant.h"
#include "MetaDefiner.h"

class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    char* name;

    void set(void* object, char* name, void* value);
    void* get(void* object, char* name);

    Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<IConstructorMeta*> constructors;
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
        return ClassType();
    }

    template <typename... Types>
    inline static void* New(Types... args)
    {
        return new ClassType(args...);
    }
};
