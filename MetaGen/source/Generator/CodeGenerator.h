
#pragma once

#include <vector>
#include <string>
#include "../Info/ClassInfo.h"

class CodeGenerator
{
public:
    std::string Generate(std::vector<ClassInfo>& classes);
    std::string Generate(ClassInfo& classInfo);
};
