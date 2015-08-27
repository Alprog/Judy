
#pragma once

#include <string>
#include <vector>
#include "Snippet.h"
#include "Statement.h"
#include "../Info/ClassInfo.h"

class CodeParser
{
public:
    void parse(std::string text);
    const std::vector<ClassInfo>& getClasses() const;

private:
    void spliceLines(std::string& text);
    void removeComments(std::string& text);
    void removeDirectives(std::string& text);
    void fixAttributeSyntax(std::string& text);
    void parseClasses(Snippet* snippet);
    void parseClassMembers(ClassInfo& classInfo, Snippet* definitionSnippet);

    std::vector<ClassInfo> classes;
};
