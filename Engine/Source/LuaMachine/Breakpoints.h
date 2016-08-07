
#pragma once

#include <unordered_map>
#include "Containers/Set.h"
#include <string>

class Breakpoints
{
    using MapType = std::unordered_map<std::string, Set<int>>;

public:
    Breakpoints();

    bool IsEmpty();
    bool IsAnySet(int line);
    bool IsSet(std::string source, int line);

    bool Clear(std::string fileName);
    Set<int> GetLines(std::string fileName);
    bool SetLines(std::string fileName, Set<int> lines);
    const MapType& getMap() const;

    void SetCaseSensitive(bool value);

private:
    void UpdateLines();

    MapType map;
    bool linesDirty;
    Set<int> lines;
    bool caseSensitive;
};
