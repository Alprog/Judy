
#include "Specifier.h"

void processSpecifiers(TokenGroup& tokens, std::vector<Specifier> specifiers)
{
    for (auto i = 0; i < tokens.size(); i++)
    {
        auto name = tokens[i]->getName();
        for (auto& s : specifiers)
        {
            if (name == s.keyword)
            {
                *s.flag = true;
                tokens.extractAt(i--);
                break;
            }
        }
    }
}
