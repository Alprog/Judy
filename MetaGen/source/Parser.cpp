
#include "Parser.h"
#include <regex>

#include <stdio.h>
#include <iostream>

const std::string singleLineComment = "//.*";
const std::string multiLineComment = "[/][*][^]*?[*][/]";
const std::string charLiteral = "'(\\\\'|[^'])*?'";        // '(\\'|[^'])*?'
const std::string stringLiteral = "\"(\\\\\"|[^\"])*?\"";  // "(\\"|[^"])*?"

void removeLineContinuations(std::string& text)
{
    text = std::regex_replace(text, std::regex("\\\\\\n"), "");   // \\\n
}

void removeComments(const std::string& text)
{
    auto comments = "(" + singleLineComment + ")|(" + multiLineComment + ")";
    auto literals = "(" + charLiteral + ")|(" + stringLiteral + ")";
    auto reg = std::regex(comments + "|" + literals);

    std::smatch match;

    auto it = std::begin(text);
    do
    {
        auto result = std::regex_search(it, std::end(text), match, reg);
        if (result)
        {
            std::cout << match[0] << std::endl << std::endl;
            it = match[0].second;
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
    removeLineContinuations(text);
    //removeComments(text);

    std::cout << text << std::endl;
    fflush(stdout);
}