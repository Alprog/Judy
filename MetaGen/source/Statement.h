
#pragma once

#include <string>
#include <vector>
#include "Token.h"

class Snippet;

struct Statement
{
    Statement(std::string& text, std::vector<std::string>* escapedLiterals);
    Statement(std::string& text, std::string& childSnippetText, std::vector<std::string>* escapedLiterals);

    const std::string& getText() const;
    const std::vector<Token>& getTokens() const;
    Snippet* getChildSnippet() const;

    bool containsToken(std::string text);
    bool isClass();
    bool hasDefinition();

private:
    void robustTokenize();
    void addToken(std::string& text);

    std::string text;
    std::vector<Token> tokens;
    const std::vector<std::string>* const escapedLiterals;
    Snippet* childSnippet;
};
