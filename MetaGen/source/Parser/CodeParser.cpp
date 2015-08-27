
#include "CodeParser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include "RegexConstants.h"

void CodeParser::parse(std::string text)
{
    spliceLines(text);
    removeComments(text);
    removeDirectives(text);
    fixAttributeSyntax(text);

    auto snippet = new Snippet(text);
    parseClasses(snippet);
    delete snippet;
}

const std::vector<ClassInfo>& CodeParser::getClasses() const
{
    return classes;
}

void CodeParser::spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex(lineContinuation), "");
}

void CodeParser::removeComments(std::string& text)
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

void CodeParser::removeDirectives(std::string& text)
{
    text = std::regex_replace(text, std::regex(directiveLine), "");
}

void CodeParser::fixAttributeSyntax(std::string& text)
{
    text = std::regex_replace(text, std::regex("__ "), "]] ");
    text = std::regex_replace(text, std::regex("__"), "[[");
}

void CodeParser::parseClasses(Snippet* snippet)
{
    for (Statement statement : snippet->getStatements())
    {
        if (statement.isClass() && statement.hasDefinition())
        {
            ClassInfo classInfo(statement.getTokens());
            if (classInfo.containsAttribute("Meta"))
            {
                auto definitionSnippet = statement.getChildSnippet();
                parseClassMembers(classInfo, definitionSnippet);
                classes.push_back(classInfo);
            }
        }
    }
}

void CodeParser::parseClassMembers(ClassInfo& classInfo, Snippet* definitionSnippet)
{
    for (Statement statement : definitionSnippet->getStatements())
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
            printf("Nested CLASS\n");
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

