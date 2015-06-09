
#include "Parser.h"
#include <regex>

using namespace std;

void parse(string& text)
{
    std::string s = "000{111{222}333}444";
    auto reg = regex("[{][^{]*?[}]");

    s = std::regex_replace(s, reg, "_");
    printf("%s\n", s.c_str());
    fflush(stdout);
}

//size_t collapse(string& text, size_t start, const char* startPattern, const char* endPattern, const char* newPattern = "")
//{
//    auto startIndex = text.find(startPattern, start);
//    if (startIndex != string::npos)
//    {
//        auto endIndex = text.find(endPattern, startIndex + strlen(startPattern)) + strlen(endPattern) - 1;
//        if (endIndex != string::npos)
//        {
//            auto length = endIndex - startIndex + 1;
//            text.replace(startIndex, length, newPattern);
//            return startIndex;
//        }
//    }
//    return string::npos;
//}

//void collapseAll(std::string& text, const char* startPattern, const char* endPattern, const char* newPattern = "")
//{
//    size_t startIndex = 0;
//    while (startIndex != string::npos)
//    {
//        startIndex = collapse(text, startIndex, "/*", "*/");
//    }
//}

//void skipLiteral(std::string::iterator& it, std::string::iterator& end)
//{
//    auto& c = *it;
//    if (c == '\'' || c == '"')
//    {
//        it++;
//        while (it != end)
//        {
//            if (*it == c && *(it - 1) != '\\')
//            {
//                it++;
//                break;
//            }
//            it++;
//        }
//    }
//}

//void filter(string& text)
//{
//    auto it = std::begin(text);
//    it = find_first(it, {"'", "\"", "/*", "//"}, std::end(text));

//    if (*it == '"' || *it == '\'')
//    {

//    }
//    else if ()
//    {

//    }

//}

//void filterComments(string& text)
//{
//    for (auto it = std::begin(text); it != std::end(text); it++)
//    {
//        skipLiteral(it, std::end(text));

//        if (*it == '/')
//        {
//            auto it2 = it + 1;
//            if (it2 != std::end(text))
//            {
//                if (*it2 == '*')
//                {

//                }
//                else if (*it2 == '/')
//                {
//                    do
//                    {
//                        it2++;
//                        if (it2 == std::end(text))
//                        {
//                            break;
//                        }
//                        else if (*it2 == '\n' || *it2 == '\r')
//                        {
//                            text.erase(it, it2);
//                            break;
//                        }
//                    }
//                    while (true);
//                    //text.erase(it, it2 - 1);
//                }
//            }
//        }
//    }

//    /*size_t i = 0;

//    bool firstSlash = false;

//    while (i < text.length())
//    {
//        auto& c = text[i];
//        if (firstSlash)
//        {
//            if (c == '/')
//            {

//            }
//        }


//        if (c == '/')
//        {
//            firstSlash = true;
//        }

//        if (c == '"')
//        {

//        }

//        i++;
//    }*/
//}



//void parse(string& text)
//{
//    filterComments(text);

//    printf(text.c_str());
//}
