
#pragma once

#include <unordered_set>
#include "List.h"
#include "Attributes.h"

template <typename T>
class _(Meta)__ Set : public std::unordered_set<T>
{
    friend class Meta;
    using base = std::unordered_set<T>;

public:
    Set() = default;

private:
    _(Serialize)__ Set(List<T> list)
        : base(std::begin(list), std::end(list))
    {
    }

    _(Serialize)__ List<T> toList()
    {
        List<T> list(size());
        std::copy(begin(), end(), std::begin(list));
        return list;
    }
};
