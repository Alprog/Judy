
#include "Document.h"
#include "TextEditor.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QLayout.h"

Document::Document(std::string filePath)
    : fullPath { filePath }
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

    editor = new TextEditor(this);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(editor);
    this->setLayout(layout);

    QFile file(fullPath.c_str());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString text = stream.readAll();
        editor->setText(text.toUtf8().constData());
        editor->emptyUndoBuffer();
        editor->setSavePoint();
        file.close();
    }

    connect(editor, SIGNAL(notifyChange()), this, SLOT(Modified()));


}

std::string Document::GetTabName()
{
    return HaveChanges() ? name + "*" : name;
}

void Document::CloseTab(int index)
{

}

void Document::Save()
{
    QFile file(fullPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        auto length = editor->length();
        auto text = editor->getText(length + 1);

        QTextStream stream(&file);
        stream << text;
        file.close();
    }

    editor->setSavePoint();
    this->OnModified();
}

bool Document::HaveChanges()
{
    return editor->modify();
}

void Document::Modified()
{
    this->OnModified();
}