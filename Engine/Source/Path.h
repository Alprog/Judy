
#pragma once

#include <string>

class Path
{
public:
    Path(const char* pathCString);
    Path(const std::string& pathString);

    static std::string GetCanonical(std::string pathString);
    static bool IsAbsolute(const std::string& pathString);

    static Path Combine(const std::string lhs, const std::string rhs);
    void Append(const std::string pathString);

    void Cd(const Path pathString);
    void CdUp();

    friend Path operator+(const Path& lhs, const Path& rhs);
    Path& operator+=(const Path& rhs);


    bool IsAbsolute() const;
    bool IsRelative() const;

    inline operator std::string&()
    {
        return canonicalPath;
    }

    inline operator const std::string&() const
    {
        return canonicalPath;
    }

    inline std::string str() const
    {
        return canonicalPath;
    }

    inline const char* c_str() const
    {
        return canonicalPath.c_str();
    }

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
