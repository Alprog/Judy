
#include "Statement.h"
#include "Snippet.h"
#include <regex>
#include "RegexConstants.h"

Statement::Statement(std::string& text, std::vector<std::string>* escapedLiterals)
    : text(text)
    , escapedLiterals(escapedLiterals)
    , childSnippet(nullptr)
{
    robustTokenize();
}

Statement::Statement(std::string& text, std::string& childSnippetText, std::vector<std::string>* escapedLiterals)
    : text(text)
    , escapedLiterals(escapedLiterals)
{
    childSnippet = new Snippet(childSnippetText, escapedLiterals);
    robustTokenize();
}

const std::string& Statement::getText() const
{
    return text;
}

const Tokens& Statement::getTokens() const
{
    return tokens;
}

Snippet* Statement::getChildSnippet() const
{
    return childSnippet;
}

bool Statement::isClass()
{
    return tokens.contains("class")
        || tokens.contains("struct")
        || tokens.contains("union");
}

bool Statement::hasDefinition()
{
    return childSnippet != nullptr;
}

void Statement::robustTokenize()
{
    auto pattern = "(" + simplexOperator + ")|(" + combinableOperator + "+)";
    text = std::regex_replace(text, std::regex(pattern), " $& ");
    text = std::regex_replace(text, std::regex(space), " ");
    text = std::regex_replace(text, std::regex("(^ )|( $)"), "");

    auto start = std::begin(text);
    for (auto it = std::begin(text); it < std::end(text); it++)
    {
        if (*it == ' ')
        {
            tokens.add(std::string(start, it));
            start = it + 1;
        }
    }
    tokens.add(std::string(start, std::end(text)));
}
