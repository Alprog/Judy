
#pragma once

#include <unordered_set>
#include "List.h"
#include "Attributes.h"

template <typename T>
class [[Meta]] Set : public std::unordered_set<T>
{
    friend class Meta;
    using base = std::unordered_set<T>;

public:
    Set() = default;

private:
    Set(List<T> list) [[Serialize]]
        : base(std::begin(list), std::end(list))
    {
    }

    [[Serialize]] List<T> ToList()
    {
        List<T> list(this->size());
        std::copy(this->begin(), this->end(), std::begin(list));
        return list;
    }
};
