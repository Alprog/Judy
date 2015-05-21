
#pragma once

#include <string>
#include <QWidget>
#include <QDateTime>

class TextEditor;

class DocumentM : public QWidget
{
    Q_OBJECT

public:
    DocumentM(std::string filePath);

    std::string GetName() { return name; }
    std::string GetFullPath() { return fullPath; }

    std::string GetTabName();

    bool IsModifiedOutside();
    void IgnoreOutsideModification();

    void Save();
    bool HaveChanges();

    void Reload();

private:
    QDateTime GetLastModifiedTime();

    std::string name;
    std::string fullPath;
    QDateTime modifiedTime;

    TextEditor* editor;

private slots:
    void Modified();
    void CloseTab(int index);

signals:
    void OnModified();
};
