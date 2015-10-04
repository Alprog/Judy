
#pragma once

#include <vector>
#include <string>
#include "../Info/ClassInfo.h"

class CodeGenerator
{
public:
    std::string GenerateCpp(std::vector<ClassInfo>& classes);

private:
    std::string GenerateIncludes(std::vector<ClassInfo>& classes);

    std::string Generate(ClassInfo& classInfo);
};
