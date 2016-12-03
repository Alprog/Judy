
#include "LuaDocument.h"
#include <QLayout>
#include "CodeEditor.h"
#include "IDE.h"
#include "Utils.h"

LuaDocument::LuaDocument()
    : TextDocument(CodeEditor::HighlightType::Lua)
{
}

DocumentType LuaDocument::getType() const
{
    return DocumentType::Lua;
}

void LuaDocument::reload()
{
    TextDocument::reload();

    auto projectPath = Path(IDE::getInstance()->settings.projectPath);
    if (startsWith(documentPath, projectPath))
    {
        auto size = projectPath.str().size();
        auto source = "@" + documentPath.str().substr(size + 1);
        editor->setSource(source);
    }

    editor->pullBreakpoints();
    editor->updateActiveLine();
}
