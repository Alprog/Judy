
#include "TextDocument.h"
#include <QVBoxLayout>

TextDocument::TextDocument(std::string documentPath, CodeEditor::HighlightType highlightType)
    : IDocument{documentPath}
{
    editor = new CodeEditor(highlightType);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(editor);
    this->setLayout(layout);

    reload();

    editor->emptyUndoBuffer();

    connect(editor, SIGNAL(notifyChange()), this, SLOT(onModified()));
}

DocumentType TextDocument::getType() const
{
    return DocumentType::Text;
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
