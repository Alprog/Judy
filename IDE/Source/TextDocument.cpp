
#include "TextDocument.h"
#include <QLayout>
#include "CodeEditor.h"
#include "Path.h"
#include "IDE.h"
#include "Utils.h"

TextDocument::TextDocument(Path documentPath, std::string extension)
    : IDocument{documentPath}
{
    auto type = CodeEditor::Type::Unknown;
    if (extension == "lua") type = CodeEditor::Type::Lua;
    if (extension == "hlsl") type = CodeEditor::Type::HLSL;
    editor = new CodeEditor(type);

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

DocumentType TextDocument::getType() const
{
    return DocumentType::Lua;
}

void TextDocument::setBinaryData(QByteArray data)
{
    editor->setText(data.constData());
    editor->setSavePoint();
}

QByteArray TextDocument::getBinaryData()
{
    auto length = editor->length();
    return editor->getText(length + 1);
}

bool TextDocument::changed() const
{
    return editor->modify();
}

void TextDocument::save()
{
    editor->setSavePoint();
    IDocument::save();
}

void TextDocument::goToLine(int line)
{
    editor->gotoLine(line - 1);
    editor->setFocus(true);
}
