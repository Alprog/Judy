
#include "TypeInfo.h"
#include "../Parser/Tokens/TokenGroup.h"
#include <regex>
#include "Specifier.h"

TypeInfo::TypeInfo()
    : isConst{false}
{
}

TypeInfo::TypeInfo(TokenGroup& tokens)
    : isConst{false}
{
    processSpecifiers(tokens,
    {
      { "const", &isConst }
    });

    name = tokens.getText();

    name = std::regex_replace(name, std::regex(" "), "");
    name = std::regex_replace(name, std::regex(","), ", ");
}
