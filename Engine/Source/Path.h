
#pragma once

#include <string>

class Path
{
    friend struct std::hash<Path>;

public:
    Path();

    Path(const char* pathCString);
    Path(const std::string& pathString);

    static std::string getCanonical(std::string pathString);
    static bool isAbsolute(const std::string& pathString);

    static Path combine(const std::string lhs, const std::string rhs);

    void append(const std::string pathString);
    void cd(const Path pathString);
    void cdUp();

    friend Path operator+(const Path& lhs, const Path& rhs);
    Path& operator+=(const Path& rhs);

    Path getParentPath() const;

    std::string getName() const;
    std::string getExtension() const;
    std::string getNameWithoutExtension() const;

    bool isEmpty() const;
    bool isAbsolute() const;
    bool isRelative() const;

    static bool isEqual(const Path& path1, const Path& path2, bool caseSensitive = true);

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
    static void fixSlashes(std::string& pathString);
    static void applyDots(std::string& pathString);

    std::string canonicalPath;
};

template<>
struct std::hash<Path>
{
    size_t operator()(const Path& path) const
    {
        return std::hash<std::string>()(path.canonicalPath);
    }
};
