
#pragma once

#include <unordered_set>
#include "List.h"

#define __Meta__
#define __Serialize__

template <typename T>
class __Meta__ Set : public std::unordered_set<T>
{
    friend class Meta;
    using base = std::unordered_set<T>;

public:
    Set() = default;

private:
    __Serialize__ Set(List<T> list)
        : base(std::begin(list), std::end(list))
    {
    }

    __Serialize__ List<T> toList()
    {
        List<T> list(size());
        std::copy(begin(), end(), std::begin(list));
        return list;
    }
};
