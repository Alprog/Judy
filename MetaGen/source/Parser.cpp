
#include "Parser.h"

using namespace std;

size_t collapse(string& text, size_t start, const char* startPattern, const char* endPattern, const char* newPattern = "")
{
    auto startIndex = text.find(startPattern, start);
    if (startIndex != string::npos)
    {
        auto endIndex = text.find(endPattern, startIndex + strlen(startPattern)) + strlen(endPattern) - 1;
        if (endIndex != string::npos)
        {
            auto length = endIndex - startIndex + 1;
            text.replace(startIndex, length, newPattern);
            return startIndex;
        }
    }
    return string::npos;
}

void collapseAll(std::string& text, const char* startPattern, const char* endPattern, const char* newPattern = "")
{
    size_t startIndex = 0;
    while (startIndex != string::npos)
    {
        startIndex = collapse(text, startIndex, "/*", "*/");
    }
}


void filterComments(string& text)
{
    size_t i = 0;

    bool firstSlash = false;

    while (i < text.length())
    {
        auto& c = text[i];
        if (firstSlash)
        {
            if (c == '/')
            {

            }
        }


        if (c == '/')
        {
            firstSlash = true;
        }

        if (c == '"')
        {

        }

        i++;
    }
}



void parse(string& text)
{
    filterComments(text);

    printf(text.c_str());
}
