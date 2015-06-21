
#pragma once

#include <vector>
#include <string>

class Tokens
{
public:
    Tokens();
    Tokens(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last);

    void add(std::string token);
    std::string getText() const;
    bool contains(std::string token) const;
    std::vector<Tokens> split(std::string delimeter);

    Tokens extract(std::string first, std::string last);
    std::vector<std::string> extractAttributes();

    std::vector<std::string> items;
};
