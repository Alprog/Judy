
#include "LuaDocement.h"
#include "TextEditor.h"

LuaDocument::LuaDocument(Path documentPath)
    : IDocument{documentPath}
{
}

QByteArray LuaDocument::GetTextData()
{
    auto length = editor->length();
    return editor->getText(length + 1);
}
