
#include "Path.h"
#include "regex"

// using unix-style slash /

Path::Path(const char*& pathCString)
    : path(pathCString)
{
}

Path::Path(const std::string& pathString)
    : path(pathString)
{
}

Path::operator std::string&()
{
    return path;
}

//explicit Path::Path(const std::string& pathString)
//{
//    return Path(pathString);
//}

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
    throw; // not implemented
}

void Path::Cd(Path path)
{
    throw; // not implemented
}

bool Path::IsAbsolute() const
{
    return false;
}

bool Path::IsRelative() const
{
    return false;
}

void Path::FixSlashes()
{
    path = std::regex_replace(path, std::regex("\\\\"), "/");
}
