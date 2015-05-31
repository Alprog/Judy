
#include "Breakpoints.h"

void Breakpoints::Add(std::string fileName, int line)
{
    map[fileName].insert(line);

    /*auto it = map.find(fileName);
    if (it != std::end(map))
    {
        it->second.insert(line);
    }
    else
    {
        map.emplace(fileName, std::unordered_set<int>(line));
    }*/
}

void Breakpoints::Remove(std::string fileName, int line)
{
    map[fileName].erase(line);

    /*auto it = map.find(fileName);
    if (it != std::end(map))
    {
        it->second.erase(line);
    }*/
}
