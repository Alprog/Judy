
#include "CodeGenerator.h"
#include <sstream>
#include <cstdio>

#if WIN
    #define snprintf _snprintf
#endif

template <typename... ArgTypes>
std::string format(const char* format, ArgTypes... args)
{
    static int size = 1024;
    static char* buffer = new char[size];

    int n = snprintf(buffer, size, format, args...);
    if (n >= 0 && n < size)
    {
        return buffer;
    }

    return "";
}

std::string CodeGenerator::Generate(std::vector<ClassInfo>& classes)
{
    std::string text;
    for (auto& classInfo : classes)
    {
        text += Generate(classInfo);
    }
    return text;
}

std::string CodeGenerator::Generate(ClassInfo& classInfo)
{
    std::stringstream stream;

    stream << "ClassDefiner<" << classInfo.name << ">" << "(this, \"" << classInfo.name << "\")" << std::endl;

    for (auto& constructor : classInfo.constructors)
    {
        stream << "    .constructor";
        if (constructor.arguments.size() > 0)
        {
            stream << "<";
            auto first = true;
            for (auto& argumentInfo : constructor.arguments)
            {
                if (!first)
                {
                    stream << ", ";
                }
                stream << argumentInfo.typeInfo.name;
                first = false;
            }
            stream << ">";
        }
        stream << "()" << std::endl;

    }

    for (auto& method : classInfo.methods)
    {
        if (!method.isOperator && !method.isStatic)
        {
            stream << "    .method(\"" << method.name << "\", &" <<
                classInfo.name << "::" << method.name << ")" << std::endl;
        }
    }

    for (auto& field : classInfo.fields)
    {
        if (!field.isStatic)
        {
            stream << "    .field(\"" << field.name << "\", &" <<
               classInfo.name << "::" << field.name << ")" << std::endl;
        }
    }

    stream << ";" << std::endl;

    return stream.str();
}


