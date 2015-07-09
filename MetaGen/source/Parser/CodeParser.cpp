
#include "CodeParser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include <vector>
#include "RegexConstants.h"
#include "Statement.h"
#include "Snippet.h"
#include "../Info/ClassInfo.h"
#include "../Generator/CodeGenerator.h"

void spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex(lineContinuation), std::string(""));
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
    text = std::regex_replace(text, std::regex(directiveLine), std::string(""));
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
        else if (statement.isClass())
        {
            printf("CLASS\n");
        }
        else
        {
            // field declaration
            for (auto& tokens : statement.getTokens().splitDeclararion())
            {
                FieldInfo fieldInfo(tokens);
                classInfo.fields.push_back(fieldInfo);
            }
        }
    }
}

void parse(std::string& text)
{
    spliceLines(text);
    removeComments(text);
    removeDirectives(text);

    text = std::regex_replace(text, std::regex("__ "), std::string("]] "));
    text = std::regex_replace(text, std::regex("__"), std::string("[["));

    CodeGenerator generator;

    auto snippet = Snippet(text);
    for (Statement statement : snippet.getStatements())
    {
        if (statement.isClass() && statement.hasDefinition())
        {
            ClassInfo classInfo(statement.getTokens());
            if (classInfo.containsAttribute("Meta"))
            {
                parseMembers(classInfo, statement);
                generator.Generate(classInfo);
            }
        }
    }

    fflush(stdout);
}
