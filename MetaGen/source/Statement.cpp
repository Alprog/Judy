
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

const std::string& Statement::getText()
{
    return text;
}

const std::vector<Token>& Statement::getTokens()
{
    return tokens;
}

bool Statement::isClass()
{
    for (auto& token : tokens)
    {
        if (token.text == "class" || token.text == "struct" || token.text == "union")
        {
            return true;
        }
    }
    return false;
}

void Statement::robustTokenize()
{
    auto pattern = "[*&()<>\\[\\]+-.,:=/%|?!~]+";
    text = std::regex_replace(text, std::regex(pattern), " $& ");
    text = std::regex_replace(text, std::regex(space), " ");
    text = std::regex_replace(text, std::regex("(^ )|( $)"), "");

    auto start = std::begin(text);
    for (auto it = std::begin(text); it < std::end(text); it++)
    {
        if (*it == ' ')
        {
            addToken(std::string(start, it));
            start = it + 1;
        }
    }
    addToken(std::string(start, std::end(text)));
}

void Statement::addToken(std::string& text)
{
    auto token = Token(text);
    tokens.push_back(token);
}
