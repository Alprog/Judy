
#include "LuaDocement.h"
#include <QLayout>
#include "CodeEditor.h"
#include "Path.h"
#include "IDE.h"
#include "Utils.h"

LuaDocument::LuaDocument(Path documentPath)
    : IDocument{documentPath}
{
    editor = new CodeEditor(nullptr);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(editor);
    this->setLayout(layout);

    Reload();

    editor->emptyUndoBuffer();

    connect(editor, SIGNAL(notifyChange()), this, SLOT(OnModified()));

    auto projectPath = Path(IDE::Instance()->settings.projectPath);
    if (StartsWith(documentPath, projectPath))
    {
        auto size = projectPath.str().size();
        auto source = "@" + documentPath.str().substr(size + 1);
        editor->setSource(source);
    }

    editor->pullBreakpoints();
    editor->updateActiveLine();
}

DocumentType LuaDocument::GetType() const
{
    return DocumentType::Lua;
}

void LuaDocument::SetBinaryData(QByteArray data)
{
    editor->setText(data.constData());
    editor->setSavePoint();
}

QByteArray LuaDocument::GetBinaryData()
{
    auto length = editor->length();
    return editor->getText(length + 1);
}

bool LuaDocument::Changed() const
{
    return editor->modify();
}

void LuaDocument::Save()
{
    editor->setSavePoint();
    IDocument::Save();
}

void LuaDocument::GoToLine(int line)
{
    editor->gotoLine(line - 1);
    editor->setFocus(true);
}
