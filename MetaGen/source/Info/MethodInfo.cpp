
#include "MethodInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

MethodInfo::MethodInfo(TokenGroup& tokens)
{
    attributes = tokens.extractAttributes();
    processArguments(tokens);

}

void MethodInfo::processArguments(TokenGroup& tokens)
{
    auto index = tokens.indexOf("()");
    if (index >= 0)
    {
        auto token = tokens.extractAt(index);
        auto content = token->cast<TokenGroup*>()->getContent();
        if (content.size() > 0)
        {
            for (auto& argumentTokens : content.split(","))
            {
                arguments.push_back(ArgumentInfo(argumentTokens));
            }
        }
    }
}
