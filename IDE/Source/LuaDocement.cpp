
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

    reload();

    editor->emptyUndoBuffer();

    connect(editor, SIGNAL(notifyChange()), this, SLOT(onModified()));

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

void LuaDocument::setBinaryData(QByteArray data)
{
    editor->setText(data.constData());
    editor->setSavePoint();
}

QByteArray LuaDocument::getBinaryData()
{
    auto length = editor->length();
    return editor->getText(length + 1);
}

bool LuaDocument::changed() const
{
    return editor->modify();
}

void LuaDocument::save()
{
    editor->setSavePoint();
    IDocument::save();
}

void LuaDocument::goToLine(int line)
{
    editor->gotoLine(line - 1);
    editor->setFocus(true);
}
