
#include "Document.h"
#include "TextEditor.h"
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QFileInfo>
#include <QDir>
#include "LuaMachine/LuaMachine.h"

DocumentM::DocumentM(std::string filePath)
    : fullPath ( filePath )
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

    editor = new TextEditor(nullptr);

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(editor);
    this->setLayout(layout);

    Reload();

    editor->emptyUndoBuffer();

    connect(editor, SIGNAL(notifyChange()), this, SLOT(OnModified()));

    auto projectPath = QDir::currentPath().toStdString();
    auto source = "@" + fullPath.substr(projectPath.length() + 1);
    editor->setSource(source);
}

void DocumentM::Reload()
{
    QFile file(fullPath.c_str());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString text = stream.readAll();
        editor->setText(text.toUtf8().constData());
        editor->setSavePoint();
        file.close();

        modifiedTime = GetLastModifiedTime();
    }
}

void DocumentM::IgnoreOutsideModification()
{
    modifiedTime = GetLastModifiedTime();
}

bool DocumentM::IsModifiedOutside()
{
    return modifiedTime < GetLastModifiedTime();
}

QDateTime DocumentM::GetLastModifiedTime()
{
    QFileInfo info(fullPath.c_str());
    return info.lastModified();
}

std::string DocumentM::GetTabName()
{
    return HaveChanges() ? name + "*" : name;
}

void DocumentM::CloseTab(int index)
{

}

void DocumentM::Save()
{
    QFile file(fullPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        auto length = editor->length();
        auto text = editor->getText(length + 1);

        QTextStream stream(&file);
        stream << text;
        file.close();

        modifiedTime = GetLastModifiedTime();
    }

    editor->setSavePoint();
    this->OnModified();
}

bool DocumentM::HaveChanges()
{
    return editor->modify();
}

void DocumentM::OnModified()
{
    this->Modified();
}
