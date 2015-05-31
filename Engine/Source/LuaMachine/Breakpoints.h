
#pragma once

#include <unordered_map>
#include <unordered_set>

class Breakpoints
{
public:
    void Add(std::string fileName, int line);
    void Remove(std::string fileName, int line);

private:
    std::unordered_map<std::string, std::unordered_set<int>> map;
};
