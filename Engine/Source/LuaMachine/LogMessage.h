
#pragma once

#include <string>

#define __Meta__

struct __Meta__ LogMessage
{
    LogMessage();
    LogMessage(std::string text);

    std::string text;
};
