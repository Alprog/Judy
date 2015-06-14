
#include "Parser.h"
#include <regex>

#include <stdio.h>
#include <iostream>
#include <vector>
#include "RegexConstants.h"
#include "Statement.h"
#include "Snippet.h"

void spliceLines(std::string& text)
{
    text = std::regex_replace(text, std::regex(lineContinuation), "");
}

void removeComments(std::string& text)
{
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

void parse(std::string& text)
{
    spliceLines(text);
    removeComments(text);
    removeDirectives(text);

    auto snippet = Snippet(text);
    for (Statement statement : snippet.getStatements())
    {
        if (statement.isClass())
        {
            std::cout << statement.getText() << std::endl;
        }


        /*for (auto& t : s.getTokens())
        {
            std::cout << t.text << std::endl;
        }*/

        //std::cout << "--" << std::endl;

//        if (s.childSnippet != nullptr)
//        {
//            for (auto& ss : s.childSnippet->getStatements())
//            {
//                std::cout << ss.text << std::endl;
//                std::cout << "--" << std::endl;
//            }
//        }
    }

    fflush(stdout);
}
