
#pragma once

#include <string>
#include <vector>
#include "ClassType.h"
#include "InheritanceInfo.h"
#include "MethodInfo.h"
#include "FieldInfo.h"
#include "MemberInfo.h"

class TokenGroup;

struct ClassInfo : MemberInfo
{
    ClassInfo(TokenGroup& tokens);

    ClassType classType;
    bool isFinal;
    std::vector<InheritanceInfo> inheritances;

    std::vector<MethodInfo> constructors;
    std::vector<MethodInfo> methods;
    std::vector<FieldInfo> fields;

    AccessModifier getDefaultAccessModifier();
    bool isAbstract();

    std::string headerName;

private:
    void processMainTokens(TokenGroup& tokens);
    void processTemplateTokens(TokenGroup& tokens);
    void processInheritanceTokens(TokenGroup& tokens);
};
