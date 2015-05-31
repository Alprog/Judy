
#include "Breakpoints.h"

bool Breakpoints::IsSet(std::string fileName, int line)
{
    auto& set = map[fileName];
    return set.find(line) != std::end(set);
}

void Breakpoints::Add(std::string fileName, int line)
{
    map[fileName].insert(line);
}

void Breakpoints::Remove(std::string fileName, int line)
{
    map[fileName].erase(line);
}

void Breakpoints::Set(std::string fileName, std::unordered_set<int> lines)
{
    map[fileName] = lines;
}
