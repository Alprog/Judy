
#pragma once

#include <string>
#include "Attributes.h"

struct [[Meta]] LogMessage
{
    LogMessage();
    LogMessage(std::string text);

    [[Serialize]] std::string text;
};
