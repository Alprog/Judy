
#include "Parser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Statement.h"
#include "Snippet.h"

const std::string singleLineComment = "//.*";
const std::string multiLineComment = "[/][*][^]*?[*][/]";
const std::string charLiteral = "'(\\\\'|[^'])*?'";        // '(\\'|[^'])*?'
const std::string stringLiteral = "\"(\\\\\"|[^\"])*?\"";  // "(\\"|[^"])*?"

const std::string lineContinuation = "\\\\\\n"; // \\\n
const std::string directiveLine = "^(\s|\t|\v)*#.*$";

void spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex(lineContinuation), "");
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

void removeDirectives(std::string& text)
{
    text = std::regex_replace(text, std::regex(directiveLine), "");
}

void collapseStrings(std::string& text)
{
    auto reg = std::regex("(" + charLiteral + ")|(" + stringLiteral + ")");
    std::match_results<std::string::iterator> match;
    auto it = std::begin(text);
    do
    {
        auto result = std::regex_search(it, std::end(text), match, reg);
        if (result)
        {
            text.replace(match[0].first + 1, match[0].second - 1, "0");
            it = match[0].first + 3;
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
    removeDirectives(text);
    collapseStrings(text);

    auto snippet = Snippet(text);
    auto statements = snippet.getStatements();

    for (auto& s : statements)
    {
        //std::cout << s.text << std::endl;
        //std::cout << "--" << std::endl;

        if (s.childSnippet != nullptr)
        {
            for (auto& ss : s.childSnippet->getStatements())
            {
                std::cout << ss.text << std::endl;
                std::cout << "--" << std::endl;
            }
        }
    }

    //std::cout << text << std::endl;
    fflush(stdout);
}
