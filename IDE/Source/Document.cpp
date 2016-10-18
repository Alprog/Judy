
#include "Document.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

IDocument::IDocument(Path documentPath)
{
    this->documentPath = documentPath;
}

void IDocument::reload()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QByteArray data = stream.readAll().toUtf8();
        setBinaryData(data);
        file.close();

        modifiedTime = getLastModifiedTime();
    }
}

void IDocument::ignoreOutsideModification()
{
    modifiedTime = getLastModifiedTime();
}

bool IDocument::isModifiedOutside()
{
    return modifiedTime < getLastModifiedTime();
}

QDateTime IDocument::getLastModifiedTime()
{
    QFileInfo info(documentPath.c_str());
    return info.lastModified();
}

std::string IDocument::getTabName()
{
    return changed() ? getName() + "*" : getName();
}

void IDocument::save()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << getBinaryData();
        file.close();
        modifiedTime = getLastModifiedTime();
    }

    this->onModified();
}

void IDocument::onModified()
{
    this->modified();
}
