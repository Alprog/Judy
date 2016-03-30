
#include "Document.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

IDocument::IDocument(Path documentPath)
{
    this->documentPath = documentPath;
}

void IDocument::Reload()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QByteArray data = stream.readAll().toUtf8();
        SetBinaryData(data);
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
    return Changed() ? GetName() + "*" : GetName();
}

void IDocument::Save()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << GetBinaryData();
        file.close();
        modifiedTime = GetLastModifiedTime();
    }

    this->OnModified();
}

void IDocument::OnModified()
{
    this->Modified();
}
