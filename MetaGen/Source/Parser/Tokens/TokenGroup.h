
#pragma once

#include "Token.h"
#include <vector>
#include <string>
#include <memory>
#include "../../Info/AttributeInfo.h"

class TokenGroup : public Token
{
private:
    using iterator = std::vector<std::shared_ptr<Token>>::iterator;

public:
    TokenGroup();
    TokenGroup(iterator first, iterator last);
    TokenGroup(std::string name, iterator first, iterator last);
    std::shared_ptr<Token>& operator[](int i);
    iterator begin();
    iterator end();
    std::vector<Token>::size_type size();

    const std::string getName() const override;
    const std::string getText() const override;

    int indexOf(std::string tokenName, int startIndex = 0) const;
    int lastIndexOf(std::string tokenName) const;
    int lastIndexOf(std::string tokenName, int startIndex) const;
    bool contains(std::string tokenName) const;

    void decay(std::string name);
    void insert(int index, std::shared_ptr<Token> token);

    std::vector<TokenGroup> split(std::string delimeter);
    void add(std::shared_ptr<Token> token);
    TokenGroup extract(int first, int last);
    std::shared_ptr<Token> extractAt(int index);
    std::shared_ptr<Token> extractLast();

    void makeBracketGroups();
    void makeTemplateGroups();
    void makeGroups(std::string openName, std::string closeName);
    std::vector<TokenGroup> splitDeclararion();

    std::vector<AttributeInfo> extractAttributes();
    TokenGroup getContent();

private:
    std::string name;
    std::vector<std::shared_ptr<Token>> tokens;
};
