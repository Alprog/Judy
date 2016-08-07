
#pragma once

#include <string>
#include <vector>
#include "Statement.h"

struct Snippet
{
    Snippet(std::string text);
    Snippet(std::string text, std::vector<std::string>* escapedLiterals);
    const std::vector<Statement>& getStatements();

private:
    void escapeLiterals();
    void parseStatements();

    std::string text;
    bool parsed;
    std::vector<Statement> statements;
    std::vector<std::string>* escapedLiterals;
};
