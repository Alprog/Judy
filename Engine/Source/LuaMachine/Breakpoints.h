
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

class Breakpoints
{
public:
    bool IsSet(std::string fileName, int line);

    void Add(std::string fileName, int line);
    void Remove(std::string fileName, int line);

    void Set(std::string fileName, std::unordered_set<int> lines);

private:
    std::unordered_map<std::string, std::unordered_set<int>> map;
};
