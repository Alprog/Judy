
#pragma once

#include <unordered_map>
#include "Containers/Set.h"
#include <string>

class Breakpoints
{
    using MapType = std::unordered_map<std::string, Set<int>>;

public:
    Breakpoints();

    bool isEmpty();
    bool isAnySet(int line);
    bool isSet(std::string source, int line);

    bool clear(std::string fileName);
    Set<int> getLines(std::string fileName);
    bool setLines(std::string fileName, Set<int> lines);
    const MapType& getMap() const;

    void setCaseSensitive(bool value);

private:
    void updateLines();

    MapType map;
    bool linesDirty;
    Set<int> lines;
    bool caseSensitive;
};
