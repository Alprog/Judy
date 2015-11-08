
#pragma once

#include <string>
#include <vector>

class TokenGroup;
class ClassInfo;

struct TypeInfo
{
    TypeInfo();
    TypeInfo(TokenGroup& tokens);

    std::string fullName;
    std::string name;
    std::vector<TypeInfo> templateArguments;
    bool isConst;

    bool isTemplate() const;

    bool isDependent(ClassInfo& classInfo);
    void refreshFullName();
};
