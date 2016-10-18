
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

bool Breakpoints::isEmpty()
{
    return map.size() == 0;
}

bool Breakpoints::isAnySet(int line)
{
    if (linesDirty)
    {
        updateLines();
    }
    return lines.find(line) != std::end(lines);
}

bool Breakpoints::isSet(std::string fileName, int line)
{
    if (!caseSensitive) fileName = lowerCase(fileName);
    auto& set = map[fileName];
    return set.find(line) != std::end(set);
}

bool Breakpoints::clear(std::string fileName)
{
    if (!caseSensitive) fileName = lowerCase(fileName);

    auto exist = map.find(fileName) != std::end(map);
    if (exist)
    {
        map.erase(fileName);
        linesDirty = true;
        return true;
    }
    return false;
}

Set<int> Breakpoints::getLines(std::string fileName)
{
    if (!caseSensitive) fileName = lowerCase(fileName);

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

bool Breakpoints::setLines(std::string fileName, Set<int> lines)
{
    if (!caseSensitive) fileName = lowerCase(fileName);

    if (lines.size() == 0)
    {
        return clear(fileName);
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

void Breakpoints::updateLines()
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

void Breakpoints::setCaseSensitive(bool value)
{
    this->caseSensitive = value;
}
