
#include "Document.h"
#include "TextEditor.h"
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QFileInfo>
#include <QDir>
#include "LuaMachine/LuaMachine.h"
#include "IDE.h"
#include "Utils.h"

IDocument::IDocument(Path documentPath)
{
    this->documentPath = documentPath;

    editor = new TextEditor(nullptr);

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

void IDocument::Reload()
{
    QFile file(documentPath.c_str());
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

void IDocument::IgnoreOutsideModification()
{
    modifiedTime = GetLastModifiedTime();
}

bool IDocument::IsModifiedOutside()
{
    return modifiedTime < GetLastModifiedTime();
}

QDateTime IDocument::GetLastModifiedTime()
{
    QFileInfo info(documentPath.c_str());
    return info.lastModified();
}

std::string IDocument::GetTabName()
{
    return HaveChanges() ? GetName() + "*" : GetName();
}

void IDocument::CloseTab(int index)
{

}

void IDocument::Save()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);

        stream << GetTextData();

        file.close();
        modifiedTime = GetLastModifiedTime();
    }

    editor->setSavePoint();
    this->OnModified();
}

bool IDocument::HaveChanges()
{
    return editor->modify();
}

void IDocument::OnModified()
{
    this->Modified();
}

void IDocument::GoToLine(int line)
{
    editor->gotoLine(line - 1);
    editor->setFocus(true);
}
