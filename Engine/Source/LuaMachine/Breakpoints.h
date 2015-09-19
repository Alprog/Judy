
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

class Breakpoints
{
    using MapType = std::unordered_map<std::string, std::unordered_set<int>>;

public:
    Breakpoints();

    bool IsEmpty();
    bool IsAnySet(int line);
    bool IsSet(std::string source, int line);

    void Add(std::string fileName, int line);
    void Remove(std::string fileName, int line);

    bool Clear(std::string fileName);
    std::unordered_set<int> Get(std::string fileName);
    bool Set(std::string fileName, std::unordered_set<int> lines);
    const MapType& getMap() const;

    void Update(Breakpoints breakpoints);

private:
    void UpdateLines();

    MapType map;
    bool linesDirty;
    std::unordered_set<int> lines;
};
