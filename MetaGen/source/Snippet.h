
#pragma once

#include <string>
#include <vector>
#include "Statement.h"

struct Snippet
{
    Snippet(std::string text);
    std::vector<Statement> getStatements();

private:
    void parseStatements();
    void trim(std::string& text);

    const std::string text;
    bool parsed;
    std::vector<Statement> statements;
};
