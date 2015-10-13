
#pragma once

#include <string>
#include "Attributes.h"

struct _(Meta)__ LogMessage
{
    LogMessage();
    LogMessage(std::string text);

    _(Serialize)__ std::string text;
};
