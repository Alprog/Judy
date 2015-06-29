
#include "Parser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include <vector>
#include "RegexConstants.h"
#include "Statement.h"
#include "Snippet.h"
#include "../Info/ClassInfo.h"

void spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex(lineContinuation), "");
}

void removeComments(std::string& text)
{
    auto reg = std::regex(comments + "|" + literals);
    std::match_results<std::string::iterator> match;
    auto it = std::begin(text);
    do
    {
        auto result = std::regex_search(it, std::end(text), match, reg);
        if (result)
        {
            if (match[1].matched || match[2].matched) // is comment
            {
                it = text.erase(match[0].first, match[0].second);
            }
            else
            {
                it = match[0].second;
            }
        }
        else
        {
            break;
        }
    }
    while (true);
}

void removeDirectives(std::string& text)
{
    text = std::regex_replace(text, std::regex(directiveLine), "");
}

void parseMembers(ClassInfo& classInfo, Statement& classStatement)
{
    auto definition = classStatement.getChildSnippet();

    for (Statement statement : definition->getStatements())
    {
        if (statement.isFunction())
        {
            MethodInfo methodInfo(statement.getTokens());
            if (methodInfo.name == classInfo.name)
            {
                classInfo.constructors.push_back(methodInfo);
            }
            else
            {
                classInfo.methods.push_back(methodInfo);
            }
        }

        //std::cout << statement.getTokens().getText() << std::endl;
    }
}

void parse(std::string& text)
{
    spliceLines(text);
    removeComments(text);
    removeDirectives(text);

    text = std::regex_replace(text, std::regex("__ "), "]] ");
    text = std::regex_replace(text, std::regex("__"), "[[");

    auto snippet = Snippet(text);
    for (Statement statement : snippet.getStatements())
    {
        if (statement.isClass() && statement.hasDefinition())
        {
            ClassInfo classInfo(statement.getTokens());
            if (classInfo.containsAttribute("Meta"))
            {
                std::cout << "-------------" << std::endl;
                std::cout << classInfo.name << std::endl;
                parseMembers(classInfo, statement);
            }
        }
    }

    fflush(stdout);
}
