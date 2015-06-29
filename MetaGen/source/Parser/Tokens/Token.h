
#pragma once

#include <string>

struct Token
{
public:
    virtual const std::string getName() const = 0;
    virtual const std::string getText() const = 0;

    template <typename T>
    T cast()
    {
        return static_cast<T>(this);
    }
};
