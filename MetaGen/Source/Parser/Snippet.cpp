
#include "Snippet.h"

#include <regex>
#include "RegexConstants.h"

Snippet::Snippet(std::string text)
    : text(text)
    , escapedLiterals(nullptr)
    , parsed(false)
{
    escapeLiterals();
}

Snippet::Snippet(std::string text, std::vector<std::string>* escapedLiterals)
    : text(text)
    , escapedLiterals(escapedLiterals)
    , parsed(false)
{
}

const std::vector<Statement>& Snippet::getStatements()
{
    if (!parsed)
    {
        parseStatements();
        parsed = true;
    }
    return statements;
}

void Snippet::escapeLiterals()
{
    escapedLiterals = new std::vector<std::string>();

    auto reg = std::regex(literals);
    std::match_results<std::string::iterator> match;
    auto it = std::begin(text);
    do
    {
        auto result = std::regex_search(it, std::end(text), match, reg);
        if (result)
        {
            auto literal = std::string(match[0].first, match[0].second);
            escapedLiterals->push_back(literal);
            auto index = escapedLiterals->size() - 1;
            auto inset = std::to_string(index);
            text.replace(match[0].first + 1, match[0].second - 1, inset);
            it = match[0].first + inset.length() + 2;
        }
        else
        {
            break;
        }
    }
    while (true);
}

void Snippet::parseStatements()
{
    std::string statementText;
    std::string childText;
    bool hasChild = false;

    auto endStatement = [&]()
    {
        if (!std::regex_match(statementText, std::regex(spaceOrEmpty)))
        {
            auto statement = hasChild
                    ? Statement(statementText, childText, escapedLiterals)
                    : Statement(statementText, escapedLiterals);
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
                endStatement(); // not always correct
            }
        }
    }
    endStatement();
}
