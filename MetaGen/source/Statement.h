
#pragma once

#include <string>
#include <vector>

class Snippet;

struct Statement
{
    Statement(std::string& text);
    Statement(std::string& text, std::string& childSnippetText);

    std::string text;
    Snippet* childSnippet;
};
