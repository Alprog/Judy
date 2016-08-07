
#include "Path.h"
#include "Utils.h"

// absolute - "C:/path" or "/path"
// relative - "path" or "./path" or "../path"
// empty path not allowed: use "." (related) or "/" (absolute) instead
// in canonical form using unix-style forward slash "/"

Path::Path()
    : canonicalPath(".")
{
}

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

    if (pathString.empty())
    {
        pathString = ".";
    }

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
    size_t lastIndex = isAbsolute ? 1 : 0;

    auto upCount = 0;
    for (size_t i = components.size() - 1; i >= lastIndex; i--)
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

        auto index = pathString.find_first_of("\\/");
        if (index == std::string::npos)
        {
            index = size;
        }
        return pathString[index - 1] == ':'; // drive
    }
    return false;
}

Path Path::Combine(const std::string lhs, const std::string rhs)
{
    if (lhs.empty())
    {
        return Path(rhs);
    }
    else
    {
        return Path(lhs + "/" + rhs);
    }
}

void Path::Append(const std::string pathString)
{
    canonicalPath = GetCanonical(canonicalPath + "/" + pathString);
}

void Path::Cd(const Path path)
{
    if (path.IsAbsolute())
    {
        canonicalPath = path.str();
    }
    else
    {
        Append(path);
    }
}

void Path::CdUp()
{
    Cd("..");
}

Path operator+(const Path& lhs, const Path& rhs)
{
    return Path::Combine(lhs, rhs);
}

Path& Path::operator+=(const Path& rhs)
{
    Append(rhs.canonicalPath);
    return *this;
}

std::string Path::GetName() const
{
    auto index = canonicalPath.find_last_of("/");
    if (index == std::string::npos)
    {
        return canonicalPath;
    }
    else
    {
        return canonicalPath.substr(index + 1);
    }
}

std::string Path::GetExtension() const
{
    auto name = GetName();
    auto index = name.find_last_of(".");
    if (index == std::string::npos)
    {
        return name;
    }
    else
    {
        return name.substr(index + 1);
    }
}

bool Path::IsAbsolute() const
{
    return IsAbsolute(canonicalPath);
}

bool Path::IsRelative() const
{
    return !IsAbsolute(canonicalPath);
}

bool Path::IsEqual(const Path& path1, const Path& path2, bool caseSensitive)
{
    if (caseSensitive)
    {
        return path1.canonicalPath == path2.canonicalPath;
    }
    else
    {
        return CaseInsensitiveCompare(path1.canonicalPath, path2.canonicalPath);
    }
}
