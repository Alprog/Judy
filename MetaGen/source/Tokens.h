
#pragma once

#include <vector>
#include <string>

class Tokens
{
public:
    void add(std::string token);
    std::string getText() const;
    bool contains(std::string token) const;

    std::vector<std::string> items;
};
