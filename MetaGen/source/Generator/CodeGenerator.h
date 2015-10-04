
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
    std::string GenerateTemplateFunctions(std::vector<ClassInfo>& classes);
    std::string GenerateMainFunction(std::vector<ClassInfo>& classes);
    std::string GenerateClassDefinition(ClassInfo& classInfo);
};
