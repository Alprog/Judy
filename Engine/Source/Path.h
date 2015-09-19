
#pragma once

#include <string>

class Path
{
public:
    Path(const char*& pathCString);
    Path(const std::string& pathString);

    operator std::string&();

    static Path Combine(Path lhs, Path rhs);
    Path* const Combine(Path other);

    void CdUp();
    void Cd(Path path);

    bool IsAbsolute() const;
    bool IsRelative() const;

private:
    void FixSlashes();

    std::string pathString;
};
