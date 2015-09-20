
#pragma once

#include <string>

class Path
{
public:
    Path(const char* pathCString);
    Path(const std::string& pathString);

    static std::string GetCanonical(std::string pathString);
    static bool IsAbsolute(const std::string& pathString);

    static Path Combine(Path lhs, Path rhs);
    Path* const Combine(Path other);

    Path& CdUp();
    Path& Cd(Path path);

    bool IsAbsolute() const;
    bool IsRelative() const;

    operator std::string&();

    std::string str() const;
    const char* c_str() const;

    inline friend bool operator ==(const Path& lhs, const Path& rhs)
    {
        return lhs.canonicalPath == rhs.canonicalPath;
    }

    inline friend bool operator !=(const Path& lhs, const Path& rhs)
    {
        return lhs.canonicalPath != rhs.canonicalPath;
    }

private:

    static void FixSlashes(std::string& pathString);
    static void ApplyDots(std::string& pathString);

    std::string canonicalPath;
};
