
#include "CodeGenerator.h"
#include <sstream>
#include <cstdio>
#include <set>

#if WIN
    #define snprintf _snprintf
#endif

const std::string tab = "    ";
const std::string tab2 = "        ";

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

std::string CodeGenerator::GenerateHeader(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << std::endl;

    for (auto& classInfo : classes)
    {
        if (classInfo.isTemplate())
        {
            stream << tab << "template <typename T>" << std::endl;
            stream << tab << "void Define" << classInfo.name << "();" << std::endl;
            stream << std::endl;
        }
    }

    return stream.str();
}

std::string CodeGenerator::GenerateSource(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << std::endl;
    stream << GenerateIncludes(classes);
    stream << std::endl;
    stream << GenerateTemplateFunctions(classes);
    stream << std::endl;
    stream << GenerateMainFunction(classes);
    stream << std::endl;
    return stream.str();
}

std::string CodeGenerator::GenerateIncludes(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << "#include \"Meta.h\"" << std::endl;
    stream << "#include \"TypeMeta.h\"" << std::endl;
    stream << "#include \"ClassDefiner.h\"" << std::endl;

    std::set<std::string> set;
    for (auto& classInfo : classes)
    {
        auto name = classInfo.headerName;
        if (set.find(name) == set.end())
        {
            stream << "#include \"" << name << "\"" << std::endl;
            set.insert(name);
        }
    }

    return stream.str();
}

std::string CodeGenerator::GenerateTemplateFunctions(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    auto first = true;
    for (auto& classInfo : classes)
    {
        if (classInfo.isTemplate())
        {
            if (!first) { stream << std::endl; }
            stream << "template <typename T>" << std::endl;
            stream << "void Meta::Define" << classInfo.name << "()" << std::endl;
            stream << "{" << std::endl;
            stream << GenerateClassDefinition(classInfo);
            stream << "}" << std::endl;
            first = false;
        }
    }
    return stream.str();
}

std::string CodeGenerator::GenerateMainFunction(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << "void Meta::DefineClasses()" << std::endl;
    stream << "{" << std::endl;

    auto first = true;
    for (auto& classInfo : classes)
    {
        if (!classInfo.isTemplate())
        {
            if (!first) { stream << std::endl; }
            stream << GenerateClassDefinition(classInfo);
            first = false;
        }
    }

    stream << "}" << std::endl;
    return stream.str();
}

std::string CodeGenerator::GenerateClassDefinition(ClassInfo& classInfo)
{
    std::stringstream stream;

    auto className = classInfo.name;
    if (classInfo.isTemplate())
    {
        stream << tab << "using type = " << className << "<T>;" << std::endl;
        className = "type";
    }

    stream << tab << "ClassDefiner<" << className << ">" << "(this, \"" << className << "\")" << std::endl;

    auto count = classInfo.templateArgumentCount;
    for (auto i = 0; i < count; i++)
    {
        auto index = count > 1 ? std::to_string(i + 1) : "";
        stream << tab2 << ".templateArgument<T" << index << ">()" << std::endl;
    }

    bool isAbstract = classInfo.isAbstract();
    if (!isAbstract)
    {
        for (auto& constructor : classInfo.constructors)
        {
            stream << tab2 << ".constructor";
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
            stream << "()";
            stream << GenerateAttributes(constructor) << std::endl;
        }
    }

    for (auto& method : classInfo.methods)
    {
        if (!method.isOperator)
        {
            auto type = method.isStatic ? "function" : "method";
            stream << tab2 << "." << type << "(\"" << method.name << "\", &" << className << "::" << method.name << ")";
            stream << GenerateAttributes(method) << std::endl;
        }
    }

    if (!isAbstract)
    {
        for (auto& field : classInfo.fields)
        {
            if (!field.isStatic)
            {
                stream << tab2 << ".field(\"" << field.name << "\", &" << className << "::" << field.name << ")";
                stream << GenerateAttributes(field) << std::endl;
            }
        }
    }

    stream << tab << ";" << std::endl;

    return stream.str();
}

std::string CodeGenerator::GenerateAttributes(MemberInfo& memberInfo)
{
    std::stringstream stream;
    for (auto& attributeInfo : memberInfo.attributes)
    {
        stream << ".attr(\"" << attributeInfo.name << "\")";
    }
    return stream.str();
}

