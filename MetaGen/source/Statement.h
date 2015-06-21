
#pragma once

#include <string>
#include <vector>
#include "Tokens.h"

class Snippet;

struct Statement
{
    Statement(std::string& text, std::vector<std::string>* escapedLiterals);
    Statement(std::string& text, std::string& childSnippetText, std::vector<std::string>* escapedLiterals);

    const std::string& getText() const;
    const Tokens& getTokens() const;
    Snippet* getChildSnippet() const;

    bool isClass();
    bool hasDefinition();

private:
    void robustTokenize();

    std::string text;
    Tokens tokens;
    const std::vector<std::string>* const escapedLiterals;
    Snippet* childSnippet;
};
