
#pragma once

#include <vector>
#include <string>
#include "../Info/ClassInfo.h"

class CodeGenerator
{
public:
    std::string GenerateHeader(std::vector<ClassInfo>& classes);
    std::string GenerateSource(std::vector<ClassInfo>& classes);

private:
    std::string GenerateIncludes(std::vector<ClassInfo>& classes);
    std::string GenerateTemplateFunctions(std::vector<ClassInfo>& templateClasses);
    std::string GenerateMainFunction(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates);
    std::string GenerateDefineTemplatesSection(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates);
    std::string GenerateClassDefinition(ClassInfo& classInfo);
    std::string GenerateMethod(std::string type, MethodInfo& method, std::string className);
    std::string GenerateAttributes(MemberInfo& memberInfo);
    std::string GenerateParametersList(ClassInfo& classInfo, bool typenames);

    std::vector<TypeInfo> GetTemplateTypes(std::vector<ClassInfo>& classes);
};
