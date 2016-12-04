
#pragma once

#include <vector>
#include <string>
#include "../Info/ClassInfo.h"

class CodeGenerator
{
public:
    std::string generateHeader(std::vector<ClassInfo>& classes);
    std::string generateSource(std::vector<ClassInfo>& classes);

private:
    std::string generateIncludes(std::vector<ClassInfo>& classes);
    std::string generateTemplateFunctions(std::vector<ClassInfo>& templateClasses);
    std::string generateMainFunction(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates);
    std::string generateDefineTemplatesSection(std::vector<ClassInfo>& realClasses, std::vector<ClassInfo>& classTemplates);
    std::string generateClassDefinition(ClassInfo& classInfo, bool isTemplate);
    std::string generateMethod(std::string type, MethodInfo& method, std::string className);
    std::string generateAttributes(MemberInfo& memberInfo);
    std::string generateParametersList(ClassInfo& classInfo, bool typenames);

    std::vector<TypeInfo> getTemplateTypes(std::vector<ClassInfo>& classes);
    bool isBindEnabled(MemberInfo& memberInfo, bool autoBind);
};
