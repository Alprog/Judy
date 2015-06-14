
#include "Snippet.h"

#include <regex>

Snippet::Snippet(std::string text)
    : text(text)
    , parsed(false)
{
}

std::vector<Statement> Snippet::getStatements()
{
    if (!parsed)
    {
        parseStatements();
        parsed = true;
    }
    return statements;
}

void Snippet::parseStatements()
{
    std::string statementText;
    std::string childText;
    bool hasChild = false;

    auto endStatement = [&]()
    {
        trim(statementText);
        if (!statementText.empty())
        {
            auto statement = hasChild ? Statement(statementText, childText) : Statement(statementText);
            statements.push_back(statement);
        }
        statementText.clear();
        childText.clear();
        hasChild = false;
    };

    auto braceLevel = 0;
    auto start = std::begin(text);
    for (auto it = std::begin(text); it < std::end(text); it++)
    {
        auto c = *it;
        if (c == ';')
        {
            if (braceLevel == 0)
            {
                statementText += std::string(start, it);
                start = it + 1;
                endStatement();
            }
        }
        else if (c == '{')
        {
            if (braceLevel == 0)
            {
                hasChild = true;
                statementText += std::string(start, it);
                start = it + 1;
            }
            braceLevel++;
        }
        else if (c == '}')
        {
            braceLevel--;
            if (braceLevel == 0)
            {
                childText += std::string(start, it);
                start = it + 1;
                endStatement();
            }
        }
    }
    endStatement();
}

void Snippet::trim(std::string& text)
{
    text = std::regex_replace(text, std::regex("( |\t|\v|\n|\r)+"), " ");
    text = std::regex_replace(text, std::regex("(^ )|( $)"), "");
}
