
#include "Statement.h"
#include "Snippet.h"
#include <regex>
#include "RegexConstants.h"
#include "Tokens/AtomToken.h"

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

TokenGroup& Statement::getTokens()
{
    return tokens;
}

Snippet* Statement::getChildSnippet() const
{
    return childSnippet;
}

bool Statement::isClass() const
{
    return (tokens.contains("class") && !tokens.contains("enum"))
        || tokens.contains("struct")
        || tokens.contains("union");
}

bool Statement::isProperty() const
{
    return tokens.contains("Property");
}

bool Statement::isUsing() const
{
    return tokens.contains("using");
}

bool Statement::isFunction() const
{
     return tokens.contains("()");
}

bool Statement::hasDefinition() const
{
    return childSnippet != nullptr;
}

void Statement::robustTokenize()
{
    auto pattern = "(" + simplexOperator + ")|(" + combinableOperator + "+)";
    auto text = this->text;

    text = std::regex_replace(text, std::regex(pattern), " $& "); // indents
    text = std::regex_replace(text, std::regex(space), " ");      // space collapse
    text = std::regex_replace(text, std::regex("(^ )|( $)"), ""); // trim

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

    tokens.makeBracketGroups();
}

void Statement::addToken(std::string text)
{
    if (text == "*>" || text == "&>")
    {
        for (auto c : text)
        {
            addToken(std::string(1, c));
        }
        return;
    }

    if (text[0] == '\'' || text[0] == '"')
    {
        auto indexString = std::string(std::begin(text) + 1, std::end(text) - 1);
        int index = std::stoi(indexString);
        if (index < escapedLiterals->size())
        {
            text = (*escapedLiterals)[index];
        }
    }    
    std::shared_ptr<Token> token { new AtomToken(text) };
    tokens.add(token);
}
