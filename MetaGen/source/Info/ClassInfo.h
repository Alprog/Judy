
#pragma once

#include <string>
#include <vector>
#include "ClassType.h"
#include "InheritanceInfo.h"
#include "MethodInfo.h"
#include "FieldInfo.h"
#include "MemberInfo.h"
#include "TypeInfo.h"
#include "PropertyInfo.h"

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
    std::vector<PropertyInfo> properties;

    AccessModifier getDefaultAccessModifier();
    bool isAbstract();

    std::string headerName;
    TypeInfo instantinateSubtype(TypeInfo typeInfo, std::vector<std::string> templateArguments);

private:
    void processMainTokens(TokenGroup& tokens);
    void processTemplateTokens(TokenGroup& tokens);
    void processInheritanceTokens(TokenGroup& tokens);
};
