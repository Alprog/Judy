
#include "Document.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>

IDocument::IDocument()
    : isNewFile {true}
{
}

void IDocument::open(Path documentPath)
{
    this->documentPath = documentPath;
    reload();
}

void IDocument::save()
{
    if (isNewFile)
    {
        saveAs();
    }
    else
    {
        resave();
    }
}

void IDocument::saveAs()
{
    auto extension = documentPath.getExtension();
    auto filter = QString("File (*.%1)").arg(extension.c_str());
    auto fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", filter);
    if (!fileName.isEmpty())
    {
        documentPath = fileName.toStdString();
        resave();
    }
}

void IDocument::resave()
{
    QFile file(documentPath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        auto data = getBinaryData();
        file.write(data);
        file.close();
        modifiedTime = getLastModifiedTime();
        isNewFile = false;
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
        isNewFile = false;
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
    return isNewFile || changed() ? getName() + "*" : getName();
}

void IDocument::onModified()
{
    this->modified();
}
