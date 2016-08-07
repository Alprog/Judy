
#pragma once

#include <string>
#include <vector>
#include "Snippet.h"
#include "Statement.h"
#include "../Info/ClassInfo.h"

class CodeParser
{
public:
    void parse(std::string text, std::string headerName = "");
    const std::vector<ClassInfo>& getClasses() const;

private:
    void spliceLines(std::string& text);
    void removeComments(std::string& text);
    void removeDirectives(std::string& text);
    void parseClasses(Snippet* snippet, std::string headerName = "");
    void parseClassMembers(ClassInfo& classInfo, Snippet* definitionSnippet);
    void checkAcessModifiers(TokenGroup& tokens);

    std::vector<ClassInfo> classes;
};
