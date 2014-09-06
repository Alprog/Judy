
#pragma once

#include "string"
#include "QWidget.h"


class TextEditor;

class Document : public QWidget
{
    Q_OBJECT

public:
    Document(std::string filePath);

    std::string Name() { return name; }
    std::string GetTabName();

    void Save();
    bool HaveChanges();

private:
    std::string name;
    std::string fullPath;


    TextEditor* editor;

private slots:
    void Modified();
    void CloseTab(int index);

signals:
    void OnModified();
};
