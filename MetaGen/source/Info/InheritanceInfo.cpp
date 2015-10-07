
#include "InheritanceInfo.h"
#include "../Parser/Tokens/TokenGroup.h"

InheritanceInfo::InheritanceInfo(TokenGroup& tokens)
    : accessModifier(AccessModifier::Private)
{
    if (tokens.size() > 0)
    {
        auto name = tokens[0]->getName();
        if (name == "private")
        {
            accessModifier = AccessModifier::Private;
            tokens.extractAt(0);
        }
        else if (name == "protected")
        {
            accessModifier = AccessModifier::Protected;
            tokens.extractAt(0);
        }
        else if (name == "public")
        {
            accessModifier = AccessModifier::Public;
            tokens.extractAt(0);
        }
    }

    type = TypeInfo(tokens);
}
