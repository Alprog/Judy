
#include "CodeParser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include "RegexConstants.h"

void CodeParser::parse(std::string text, std::string headerName)
{
    spliceLines(text);
    removeComments(text);
    removeDirectives(text);

    auto snippet = new Snippet(text);
    parseClasses(snippet, headerName);
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

void CodeParser::parseClasses(Snippet* snippet, std::string headerName)
{
    for (Statement statement : snippet->getStatements())
    {
        if (statement.isClass() && statement.hasDefinition())
        {
            ClassInfo classInfo(statement.getTokens());
            classInfo.headerName = headerName;
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
    auto statements = definitionSnippet->getStatements();
    auto index = 0;
    while (index < statements.size())
    {
        auto& statement = statements[index++];
        auto& statementTokens = statement.getTokens();
        checkAcessModifiers(statementTokens);

        if (statement.isFunction())
        {
            MethodInfo methodInfo(statementTokens);
            if (methodInfo.name == classInfo.name)
            {
                classInfo.constructors.push_back(methodInfo);
            }
            else
            {
                classInfo.methods.push_back(methodInfo);
            }
        }
        else if (statement.isProperty())
        {
            PropertyInfo propertyInfo(statementTokens);
            for (auto i = 0; i < 2; i++)
            {
                if (index < statements.size())
                {
                    auto& statement = statements[index++];
                    auto& tokens = statement.getTokens();
                    checkAcessModifiers(statementTokens);
                    if (statement.isFunction())
                    {
                        propertyInfo.addMethod(tokens);
                    }
                }
            }
            classInfo.properties.push_back(propertyInfo);
        }
        else if (statement.isClass())
        {
            //printf("Nested CLASS\n");
        }
        else if (statement.isUsing())
        {
            // nothing
        }
        else
        {
            // field declaration
            for (auto& tokens : statementTokens.splitDeclararion())
            {
                FieldInfo fieldInfo(tokens);
                classInfo.fields.push_back(fieldInfo);
            }
        }
    }
}

void CodeParser::checkAcessModifiers(TokenGroup& tokens)
{
    auto name = tokens[0]->getName();
    if (name == "public" || name == "protected" || name == "private")
    {
        tokens.extract(0, 2);
    }
}

