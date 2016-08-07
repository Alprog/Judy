
#include "Breakpoints.h"
#include "Utils.h"

Breakpoints::Breakpoints()
    : linesDirty{true}
    , caseSensitive{true}
{
#if WIN
    caseSensitive = false;
#endif
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
    if (!caseSensitive) fileName = LowerCase(fileName);
    auto& set = map[fileName];
    return set.find(line) != std::end(set);
}

bool Breakpoints::Clear(std::string fileName)
{
    if (!caseSensitive) fileName = LowerCase(fileName);

    auto exist = map.find(fileName) != std::end(map);
    if (exist)
    {
        map.erase(fileName);
        linesDirty = true;
        return true;
    }
    return false;
}

Set<int> Breakpoints::GetLines(std::string fileName)
{
    if (!caseSensitive) fileName = LowerCase(fileName);

    auto exist = map.find(fileName) != std::end(map);
    if (exist)
    {
        return map[fileName];
    }
    else
    {
        return Set<int>();
    }
}

bool Breakpoints::SetLines(std::string fileName, Set<int> lines)
{
    if (!caseSensitive) fileName = LowerCase(fileName);

    if (lines.size() == 0)
    {
        return Clear(fileName);
    }

    auto exist = map.find(fileName) != std::end(map);
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

void Breakpoints::SetCaseSensitive(bool value)
{
    this->caseSensitive = value;
}
