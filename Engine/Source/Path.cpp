
#include "Path.h"
#include "Utils.h"

// absolute - "C:/path" or "/path"
// relative - "path" or "./path" or "../path"
// using unix-style forward slash /

Path::Path(const char* pathCString)
{
    canonicalPath = GetCanonical(pathCString);
}

Path::Path(const std::string& pathString)
{
    canonicalPath = GetCanonical(pathString);
}

std::string Path::GetCanonical(std::string pathString)
{
    FixSlashes(pathString);
    ApplyDots(pathString);

#if WIN
    ToLower(pathString);
#endif

    return pathString;
}

void Path::FixSlashes(std::string& pathString)
{
    // fix backslashes
    Replace(pathString, "\\", "/");

    // remove slash duplicates
    Replace(pathString, "//", "/");

    // remove last slash
    auto size = pathString.size();
    if (size > 1 && pathString[size - 1] == '/')
    {
        pathString.erase(size - 1);
    }
}

void Path::ApplyDots(std::string& pathString)
{
    auto components = Split(pathString, "/");
    auto begin = std::begin(components);
    bool changed = false;

    bool isAbsolute = IsAbsolute(pathString);
    auto lastIndex = isAbsolute ? 1 : 0;

    auto upCount = 0;
    for (int i = components.size() - 1; i >= lastIndex; i--)
    {
        auto component = components[i];
        if (component == ".")
        {
            components.erase(begin + i);
            changed = true;
        }
        else if (component == "..")
        {
            upCount++;
        }
        else if (upCount > 0)
        {
            auto start = begin + i;
            components.erase(start, start + 2);
            changed = true;
            upCount--;
        }
    }

    if (isAbsolute)
    {
        auto start = begin + 1;
        components.erase(start, start + upCount);
        changed = true;
    }

    if (changed)
    {
        pathString = Join(components, "/");
    }
}

bool Path::IsAbsolute(const std::string& pathString)
{
    auto size = pathString.size();
    if (size > 0)
    {
        if (pathString[0] == '/' || pathString[0] == '\\')
        {
            return true;
        }

        auto index = pathString.find_first_of('\\/');
        if (index == std::string::npos)
        {
            index = size;
        }
        return pathString[index - 1] == ':'; // drive
    }
    return false;
}


Path Path::Combine(Path lhs, Path rhs)
{
    lhs.str() + "/" + rhs.str();

    throw; // not implemented
}

Path* const Path::Combine(Path other)
{
    return this;
}

Path& Path::CdUp()
{
    return Cd("..");
}

Path& Path::Cd(Path path)
{
    if (path.IsAbsolute())
    {
        canonicalPath = path.str();
    }
    else
    {
        Combine(path);
    }
    return *this;
}

bool Path::IsAbsolute() const
{
    return IsAbsolute(canonicalPath);
}

bool Path::IsRelative() const
{
    return !IsAbsolute(canonicalPath);
}


Path::operator std::string&()
{
    return canonicalPath;
}

std::string Path::str() const
{
    return canonicalPath;
}

const char* Path::c_str() const
{
    return canonicalPath.c_str();
}
