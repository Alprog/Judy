
#pragma once

#include <string>
#include <vector>
#include "Tokens/TokenGroup.h"

class Snippet;

struct Statement
{
    Statement(std::string& text, std::vector<std::string>* escapedLiterals);
    Statement(std::string& text, std::string& childSnippetText, std::vector<std::string>* escapedLiterals);

    const std::string& getText() const;
    TokenGroup& getTokens();
    Snippet* getChildSnippet() const;

    bool isClass();
    bool hasDefinition();

private:
    void robustTokenize();
    void addToken(std::string text);

    std::string text;
    TokenGroup tokens;
    const std::vector<std::string>* const escapedLiterals;
    Snippet* childSnippet;
};
