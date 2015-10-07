
#pragma once

#include <string>
#include <QWidget>
#include <QDateTime>
#include "Path.h"

class TextEditor;

class DocumentM : public QWidget
{
    Q_OBJECT

public:
    DocumentM(Path documentPath);

    Path GetPath() { return documentPath; }
    std::string GetName() { return documentPath.GetName(); }

    void GoToLine(int line);
    std::string GetTabName();

    bool IsModifiedOutside();
    void IgnoreOutsideModification();

    void Save();
    bool HaveChanges();

    void Reload();

private:
    QDateTime GetLastModifiedTime();
    virtual QByteArray GetTextData() = 0;

private slots:
    void OnModified();
    void CloseTab(int index);

signals:
    void Modified();

protected:
    Path documentPath;
    QDateTime modifiedTime;

    TextEditor* editor;
};
