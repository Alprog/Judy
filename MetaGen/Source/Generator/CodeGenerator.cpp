
#include "CodeGenerator.h"
#include <sstream>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include "../Info/TypeInfo.h"
#include <regex>

#if WIN
    #define snprintf _snprintf
#endif

template <int count>
const std::string tab = std::string(count * 4, ' ');

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

std::string CodeGenerator::generateHeader(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << std::endl;

    for (auto& classInfo : classes)
    {
        if (classInfo.isTemplate())
        {
            auto list = generateParametersList(classInfo, true);
            stream << tab<1> << "template <" << list << ">" << std::endl;
            stream << tab<1> << "void define" << classInfo.name << "();" << std::endl;
            stream << std::endl;
        }
    }

    return stream.str();
}

std::string CodeGenerator::generateSource(std::vector<ClassInfo>& classes)
{
    std::vector<ClassInfo> classTemplates;
    std::vector<ClassInfo> realClasses;
    for (auto& classInfo : classes)
    {
        auto* vector = classInfo.isTemplate() ? &classTemplates : &realClasses;
        vector->push_back(classInfo);
    }

    std::stringstream stream;
    stream << std::endl;
    stream << generateIncludes(classes);
    stream << std::endl;
    stream << generateTemplateFunctions(classTemplates);
    stream << std::endl;
    stream << generateMainFunction(realClasses, classTemplates);
    stream << std::endl;
    return stream.str();
}

std::string CodeGenerator::generateIncludes(std::vector<ClassInfo>& classes)
{
    std::stringstream stream;
    stream << "#include <Meta.h>" << std::endl;
    stream << "#include <TypeMeta.h>" << std::endl;
    stream << "#include <ClassDefiner.h>" << std::endl;
    stream << "#include <RendererFrontend.h>" << std::endl;

    std::unordered_set<std::string> set;
    for (auto& classInfo : classes)
    {
        auto name = classInfo.headerName;
        if (set.find(name) == set.end())
        {
            stream << "#include <" << name << ">" << std::endl;
            set.insert(name);
        }
    }

    return stream.str();
}

std::string CodeGenerator::generateTemplateFunctions(std::vector<ClassInfo>& templateClasses)
{
    std::stringstream stream;
    auto first = true;
    for (auto& classInfo : templateClasses)
    {
        if (!first) { stream << std::endl; }
        auto list = generateParametersList(classInfo, true);
        stream << "template <" << list << ">" << std::endl;
        stream << "void Meta::define" << classInfo.name << "()" << std::endl;
        stream << "{" << std::endl;
        stream << generateClassDefinition(classInfo, true);
        stream << "}" << std::endl;
        first = false;
    }
    return stream.str();
}

std::string CodeGenerator::generateMainFunction(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates)
{
    std::stringstream stream;
    stream << "void Meta::defineClasses()" << std::endl;
    stream << "{" << std::endl;

    stream << generateDefineTemplatesSection(realClasses, classTemplates);

    for (auto& classInfo : realClasses)
    {
        stream << std::endl << generateClassDefinition(classInfo, false);
    }

    stream << "}" << std::endl;
    return stream.str();
}

std::string CodeGenerator::generateDefineTemplatesSection(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates)
{
    struct Helper
    {
        ClassInfo* classInfo;
        std::vector<TypeInfo> templates;
    };

    // helper storage for class-dependent templates
    std::unordered_map<std::string, Helper> map;
    for (auto& classInfo : classTemplates)
    {
        map[classInfo.name] = Helper{ &classInfo, {} };
    }

    std::vector<TypeInfo> templateInstances;

    // find template instantiations from classes
    for (auto& typeInfo : getTemplateTypes(realClasses))
    {
        if (map.find(typeInfo.name) != std::end(map)) // known template class
        {
            templateInstances.push_back(typeInfo);
        }
    }

    // the same from class templates + find and store class-dependent templates for later instantination
    for (auto& classInfo : classTemplates)
    {
        std::vector<ClassInfo> vector {classInfo};
        for (auto& typeInfo : getTemplateTypes(vector))
        {
            if (map.find(typeInfo.name) != std::end(map)) // known template class
            {
                if(typeInfo.isDependent(classInfo))
                {
                    map[classInfo.name].templates.push_back(typeInfo);
                }
                else
                {
                    templateInstances.push_back(typeInfo);
                }
            }
        }
    }

    // instantinate more types (recursive)
    std::unordered_set<std::string> set;
    for (auto typeInfo : templateInstances)
    {
        set.insert(typeInfo.fullName);
    }
    for (auto i = 0; i < templateInstances.size(); i++)
    {
        auto& typeInfo = templateInstances[i];
        auto helper = map[typeInfo.name];
        auto arguments = typeInfo.templateArguments;
        for (auto templateInfo : helper.templates)
        {
            auto instance = helper.classInfo->instantinateSubtype(templateInfo, arguments);
            if (set.find(instance.fullName) == std::end(set))
            {
                templateInstances.push_back(instance);
                set.insert(instance.fullName);
            }
        }
    }

    // generate define text
    std::stringstream stream;
    for (auto& typeInfo : templateInstances)
    {
        stream << tab<1> << "define" << typeInfo.fullName << "();" << std::endl;
    }
    return stream.str();
}

std::vector<TypeInfo> CodeGenerator::getTemplateTypes(std::vector<ClassInfo>& classes)
{
    std::vector<TypeInfo*> typeRefs;
    for (auto& classInfo : classes)
    {
        for (auto& fieldInfo : classInfo.fields)
        {
            typeRefs.push_back(&fieldInfo.type);
        }
        for (auto& inheritanceInfo : classInfo.inheritances)
        {
            typeRefs.push_back(&inheritanceInfo.type);
        }
        for (auto& methodInfo : classInfo.methods)
        {
            typeRefs.push_back(&methodInfo.returnType);
            for (auto& argumentInfo : methodInfo.arguments)
            {
                typeRefs.push_back(&argumentInfo.type);
            }
        }
        for (auto& methodInfo : classInfo.constructors)
        {
            typeRefs.push_back(&methodInfo.returnType);
            for (auto& argumentInfo : methodInfo.arguments)
            {
                typeRefs.push_back(&argumentInfo.type);
            }
        }
    }

    for (auto i = 0; i < typeRefs.size(); i++)
    {
        for (auto& type : typeRefs[i]->templateArguments)
        {
            typeRefs.push_back(&type);
        }
    }

    std::vector<TypeInfo> types;
    std::unordered_set<std::string> names;
    for (TypeInfo* typeRef : typeRefs)
    {
        if (typeRef->isTemplate())
        {
            auto name = typeRef->fullName;
            if (names.find(name) == std::end(names))
            {
                types.push_back(*typeRef);
                names.insert(name);
            }
        }
    }
    return types;
}

std::string CodeGenerator::generateClassDefinition(ClassInfo& classInfo, bool isTemplate)
{
    std::stringstream stream;

    auto className = classInfo.name;
    auto classFullName = className;
    if (classInfo.isTemplate())
    {
        classFullName = className + "<" + generateParametersList(classInfo, false) + ">";
        stream << tab<1> << "using type = " << classFullName << ";" << std::endl;
        className = "type";
    }

    stream << tab<1> << "ClassDefiner<" << className << ">" << "(this, \"" << classFullName << "\")" << std::endl;

    // template arguments
    for (auto& parameter : classInfo.templateParameters)
    {
        stream << tab<2>;
        stream << (isTemplate ? ".template templateArgument" : ".templateArgument");
        stream << "<" << parameter << ">()" << std::endl;
    }

    // base classes
    for (auto& inheritanceInfo : classInfo.inheritances)
    {
        if (inheritanceInfo.type.name == "Singleton")
        {
            stream << tab<2>;
            stream << ".function(\"getInstance\", &" << className << "::getInstance)" << std::endl;
        }
        else
        {
            stream << tab<2>;
            stream << (isTemplate ? ".template base" : ".base");
            stream << "<" << inheritanceInfo.type.fullName << ">()" << std::endl;
        }
    }

    // constructors
    bool isAbstract = classInfo.isAbstract();
    if (!isAbstract)
    {
        for (auto& constructor : classInfo.constructors)
        {
            stream << tab<2>;
            if (constructor.arguments.size() == 0)
            {
                stream << ".constructor";
            }
            else
            {
                stream << (isTemplate ? ".template constructor" : ".constructor");
                stream << "<";
                auto first = true;
                for (auto& argumentInfo : constructor.arguments)
                {
                    if (!first)
                    {
                        stream << ", ";
                    }
                    stream << argumentInfo.type.fullName;
                    first = false;
                }
                stream << ">";
            }
            stream << "()";
            stream << generateAttributes(constructor) << std::endl;
        }
    }

    // methods
    for (auto& method : classInfo.methods)
    {
        if (!method.isOperator && !method.isFriend && !method.containsAttribute("Ignore"))
        {
            auto type = method.isStatic ? "function" : "method";
            stream << tab<2> << generateMethod(type, method, className);
        }
    }

    // properties
    for (auto& property : classInfo.properties)
    {
        stream << tab<2> << ".property(\"" << property.name << "\")" << generateAttributes(property) << std::endl;
        if (property.hasGetter())
        {
            stream << tab<3> << generateMethod("getter", property.getter, className);
        }
        if (property.hasSetter())
        {
            stream << tab<3> << generateMethod("setter", property.setter, className);
        }
    }

    // fields
    //if (!isAbstract)
    {
        for (auto& field : classInfo.fields)
        {
            if (!field.isStatic)
            {
                stream << tab<2> << ".field(\"" << field.name << "\", &" << className << "::" << field.name << ")";
                stream << generateAttributes(field) << std::endl;
            }
        }
    }

    stream << tab<1> << ";" << std::endl;

    return stream.str();
}

std::string CodeGenerator::generateMethod(std::string type, MethodInfo& method, std::string className)
{
    std::stringstream stream;

    auto methodName = method.name;

    auto bindAttribute = method.getAttribute("Bind");
    if (bindAttribute != nullptr && !bindAttribute->value.empty())
    {
        methodName = std::regex_replace(bindAttribute->value, std::regex("\""), "");
    }

    stream << "." << type << "(\"" << methodName << "\", &" << className << "::" << method.name << ")";
    stream << generateAttributes(method) << std::endl;
    return stream.str();
}

std::string CodeGenerator::generateAttributes(MemberInfo& memberInfo)
{
    std::stringstream stream;
    for (auto& attributeInfo : memberInfo.attributes)
    {
        if (attributeInfo.name != "Bind")
        {
            stream << ".attr(\"" << attributeInfo.name << "\")";
        }
    }
    return stream.str();
}

std::string CodeGenerator::generateParametersList(ClassInfo& classInfo, bool typenames)
{
    std::stringstream stream;
    auto first = true;
    for (auto& parameter : classInfo.templateParameters)
    {
        if (!first) { stream << ", "; }
        if (typenames) { stream << "typename "; }
        stream << parameter;
        first = false;
    }
    return stream.str();
}
