
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"
#include <regex>

TypeInfo::TypeInfo()
{
}

TypeInfo::TypeInfo(TokenGroup& tokens)
{
    name = tokens.getText();

    name = std::regex_replace(name, std::regex(" "), "");
    name = std::regex_replace(name, std::regex(","), ", ");
}
