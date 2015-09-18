
#include "Breakpoints.h"

Breakpoints::Breakpoints()
    : linesDirty{true}
{
}

bool Breakpoints::IsEmpty()
{
    return map.size() == 0;
}

bool Breakpoints::IsAnySet(int line)
{
    if (linesDirty)
    {
        UpdateLines();
    }
    return lines.find(line) != std::end(lines);
}

bool Breakpoints::IsSet(std::string fileName, int line)
{
    auto& set = map[fileName];
    return set.find(line) != std::end(set);
}

void Breakpoints::Add(std::string fileName, int line)
{
    map[fileName].insert(line);
    linesDirty = true;
}

void Breakpoints::Remove(std::string fileName, int line)
{
    map[fileName].erase(line);
    linesDirty = true;
}

bool Breakpoints::Clear(std::string fileName)
{
    bool exist = map.find(fileName) != std::end(map);
    if (exist)
    {
        map.erase(fileName);
        linesDirty = true;
        return true;
    }
    return false;
}

bool Breakpoints::Set(std::string fileName, std::unordered_set<int> lines)
{
    if (lines.size() == 0)
    {
        return Clear(fileName);
    }

    bool exist = map.find(fileName) != std::end(map);
    if (exist)
    {
        if (map[fileName] == lines)
        {
            return false;
        }
    }

    map[fileName] = lines;
    linesDirty = true;
    return true;
}

void Breakpoints::UpdateLines()
{
    lines.clear();
    for (auto& pair : map)
    {
        for (auto line : pair.second)
        {
            lines.insert(line);
        }
    }
    linesDirty = false;
}

const Breakpoints::MapType& Breakpoints::getMap() const
{
    return map;
}
