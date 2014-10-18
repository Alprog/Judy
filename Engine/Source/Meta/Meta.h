
#pragma once

#include <vector>

class TypeMeta;

class Meta
{
public:
    static Meta* Instance();

    std::vector<TypeMeta*> Types;

private:
    Meta();

    //template <typename T>
    //MetaDefiner<T>* Define();
};
