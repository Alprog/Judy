
#include "Document.h"
#include "TextEditor.h"

Document::Document()
    : name { "New" }
    , fullPath { }
    , changed { false }
{
    editor = new TextEditor;
}

Document::Document(std::string filePath)
    : fullPath { filePath }
    , changed { false }
{
    auto index = filePath.find_last_of("\\/");
    if (index == std::string::npos)
    {
        name = fullPath;
    }
    else
    {
        index += 1;
        auto size = fullPath.size() - index;
        name = fullPath.substr(index, size);
    }

    editor = new TextEditor;
}
