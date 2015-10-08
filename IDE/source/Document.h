
#pragma once

#include <string>
#include <QWidget>
#include <QDateTime>
#include "Path.h"
#include "DocumentType.h"

class IDocument : public QWidget
{
    Q_OBJECT

public:
    IDocument(Path documentPath);
    virtual DocumentType GetType() const = 0;

    Path GetPath() { return documentPath; }
    std::string GetName() { return documentPath.GetName(); }
    std::string GetTabName();

    bool IsModifiedOutside();
    void IgnoreOutsideModification();

    virtual void Save();
    virtual bool Changed() const = 0;

    void Reload();

private:
    QDateTime GetLastModifiedTime();
    virtual void SetBinaryData(QByteArray data) = 0;
    virtual QByteArray GetBinaryData() = 0;

private slots:
    void OnModified();

signals:
    void Modified();

protected:
    Path documentPath;
    QDateTime modifiedTime;
};
