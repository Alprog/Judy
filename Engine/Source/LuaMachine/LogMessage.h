
#pragma once

#include <string>

#define __Meta__
#define __Serialize__

struct __Meta__ LogMessage
{
    LogMessage();
    LogMessage(std::string text);

    __Serialize__ std::string text;
};
