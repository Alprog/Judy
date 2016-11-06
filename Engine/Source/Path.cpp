
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
    canonicalPath = getCanonical(pathCString);
}

Path::Path(const std::string& pathString)
{
    canonicalPath = getCanonical(pathString);
}

std::string Path::getCanonical(std::string pathString)
{
    fixSlashes(pathString);
    applyDots(pathString);

    if (pathString.empty())
    {
        pathString = ".";
    }

    return pathString;
}

void Path::fixSlashes(std::string& pathString)
{
    // fix backslashes
    replace(pathString, "\\", "/");

    // remove slash duplicates
    replace(pathString, "//", "/");

    // remove last slash
    auto size = pathString.size();
    if (size > 1 && pathString[size - 1] == '/')
    {
        pathString.erase(size - 1);
    }
}

void Path::applyDots(std::string& pathString)
{
    auto components = split(pathString, "/");
    auto begin = std::begin(components);
    bool changed = false;

    bool isAbsolute = Path::isAbsolute(pathString);
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
        pathString = join(components, "/");
    }
}

bool Path::isAbsolute(const std::string& pathString)
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

Path Path::combine(const std::string lhs, const std::string rhs)
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

void Path::append(const std::string pathString)
{
    canonicalPath = getCanonical(canonicalPath + "/" + pathString);
}

void Path::cd(const Path path)
{
    if (path.isAbsolute())
    {
        canonicalPath = path.str();
    }
    else
    {
        append(path);
    }
}

void Path::cdUp()
{
    cd("..");
}

Path operator+(const Path& lhs, const Path& rhs)
{
    return Path::combine(lhs, rhs);
}

Path& Path::operator+=(const Path& rhs)
{
    append(rhs.canonicalPath);
    return *this;
}

Path Path::getParentPath() const
{
    auto index = canonicalPath.find_last_of("/");
    if (index == std::string::npos)
    {
        return "";
    }
    else
    {
        return canonicalPath.substr(0, index);
    }
}

std::string Path::getName() const
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

std::string Path::getNameWithoutExtension() const
{
    auto name = getName();
    auto index = name.find_last_of(".");
    if (index == std::string::npos)
    {
        return name;
    }
    else
    {
        return name.substr(0, index);
    }
}

std::string Path::getExtension() const
{
    auto name = getName();
    auto index = name.find_last_of(".");
    if (index == std::string::npos)
    {
        return "";
    }
    else
    {
        return name.substr(index + 1);
    }
}

bool Path::isAbsolute() const
{
    return isAbsolute(canonicalPath);
}

bool Path::isRelative() const
{
    return !isAbsolute(canonicalPath);
}

bool Path::isEqual(const Path& path1, const Path& path2, bool caseSensitive)
{
    if (caseSensitive)
    {
        return path1.canonicalPath == path2.canonicalPath;
    }
    else
    {
        return caseInsensitiveCompare(path1.canonicalPath, path2.canonicalPath);
    }
}
