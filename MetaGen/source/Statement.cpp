
#include "Statement.h"
#include "Snippet.h"

Statement::Statement(std::string& text)
    : text(text)
    , childSnippet(nullptr)
{
}

Statement::Statement(std::string& text, std::string& childSnippetText)
    : text(text)
{
    childSnippet = new Snippet(childSnippetText);
}
