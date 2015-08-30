
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
    for (auto& classInfo : classes)
    {
        std::string text = Generate(classInfo);
        printf("%s \n", text.c_str());
    }
    return nullptr;
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
        if (!method.isOperator)
        {
            stream << "    .method(\"" << method.name << "\", &" <<
                classInfo.name << "::" << method.name << ")" << std::endl;
        }
    }

    for (auto& field : classInfo.fields)
    {
        stream << "    .field(\"" << field.name << "\", &" <<
           classInfo.name << "::" << field.name << ")" << std::endl;
    }

    stream << ";" << std::endl;

    return stream.str();
}


