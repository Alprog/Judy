
#include "TextDocument.h"
#include <QVBoxLayout>

TextDocument::TextDocument(CodeEditor::HighlightType highlightType)
{
    editor = new CodeEditor();
    editor->setHighlightType(highlightType);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(editor);
    this->setLayout(layout);

    editor->emptyUndoBuffer();

    connect(editor, SIGNAL(notifyChange()), this, SLOT(onModified()));
}

DocumentType TextDocument::getType() const
{
    return DocumentType::Text;
}

void TextDocument::setBinaryData(QByteArray data)
{
    std::string text = data.constData();
    editor->setText(text);
    editor->setSavePoint();
}

QByteArray TextDocument::getBinaryData() const
{
    auto length = editor->length();
    return editor->getText(length + 1);
}

std::string TextDocument::getText() const
{
    auto length = editor->length();
    auto data = editor->getText(length + 1);
    return data.constData();
}

void TextDocument::setText(std::string text)
{
    editor->setText(text);
    editor->setSavePoint();
}

void TextDocument::setReadOnly(bool value)
{
    editor->setReadOnly(value);
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
