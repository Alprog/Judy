
#include "LuaDocument.h"
#include <QLayout>
#include "CodeEditor.h"
#include "IDE.h"
#include "Utils.h"

LuaDocument::LuaDocument(Path documentPath)
    : TextDocument{documentPath, CodeEditor::HighlightType::Lua}
{
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

DocumentType LuaDocument::getType() const
{
    return DocumentType::Lua;
}
