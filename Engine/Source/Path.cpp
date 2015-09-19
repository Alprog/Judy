
#include "Path.h"
#include "regex"

// absolute - "C:/path" or "/path"
// relative - "path" or "./path" or "../path"
// using unix-style forward slash /

Path::Path(const char*& pathCString)
    : pathString(pathCString)
{
    FixSlashes();
}

Path::Path(const std::string& pathString)
    : pathString(pathString)
{
    FixSlashes();
}

Path::operator std::string&()
{
    return pathString;
}

Path Path::Combine(Path lhs, Path rhs)
{
    throw; // not implemented
}

Path* const Path::Combine(Path other)
{
    return this;
}

void Path::CdUp()
{
    Cd("..");
}

void Path::Cd(Path path)
{
    throw; // not implemented
}

bool Path::IsAbsolute() const
{
    if (pathString.size() > 0)
    {
        auto firstChar = pathString[0];
        if (firstChar == '/') { return true; }
        if (firstChar == '.') { return false; }
        auto index = pathString.find('/');
        if (index != std::string::npos)
        {
            return pathString[index - 1] == ':'; // drive (or url?)
        }
    }
    return false;
}

bool Path::IsRelative() const
{
    return !IsAbsolute();
}

void Path::FixSlashes()
{
    // change this later
    pathString = std::regex_replace(pathString, std::regex("\\\\"), "/");
    pathString = std::regex_replace(pathString, std::regex("//"), "/");
}
