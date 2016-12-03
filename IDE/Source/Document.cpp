
#include "Document.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

void IDocument::open(Path documentPath)
{
    this->documentPath = documentPath;
    reload();
}

void IDocument::save()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        auto data = getBinaryData();
        file.write(data);
        file.close();
        modifiedTime = getLastModifiedTime();
    }

    this->onModified();
}

void IDocument::reload()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
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

void IDocument::onModified()
{
    this->modified();
}
