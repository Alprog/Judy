
#include "Parser.h"
#include <regex>

#include <stdio.h>
#include <iostream>

const std::string singleLineComment = "//.*";
const std::string multiLineComment = "[/][*][^]*?[*][/]";
const std::string charLiteral = "'(\\\\'|[^'])*?'";        // '(\\'|[^'])*?'
const std::string stringLiteral = "\"(\\\\\"|[^\"])*?\"";  // "(\\"|[^"])*?"

void spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex("\\\\\\n"), "");   // \\\n
}

void removeComments(std::string& text)
{
    auto comments = "(" + singleLineComment + ")|(" + multiLineComment + ")";
    auto literals = "(" + charLiteral + ")|(" + stringLiteral + ")";
    auto reg = std::regex(comments + "|" + literals);

    std::match_results<std::string::iterator> match;
    auto it = std::begin(text);
    do
    {
        auto result = std::regex_search(it, std::end(text), match, reg);
        if (result)
        {
            if (match[1].matched || match[2].matched) // is comment
            {
                it = text.erase(match[0].first, match[0].second);
            }
            else
            {
                it = match[0].second;
            }
        }
        else
        {
            break;
        }
    }
    while (true);
}

void parse(std::string& text)
{
    spliceLines(text);
    removeComments(text);

    std::cout << text << std::endl;
    fflush(stdout);
}
