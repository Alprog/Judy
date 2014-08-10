
#pragma once

#include "string"
#include "QWidget.h"

class Document
{
public:
    Document();
    Document(std::string filePath);

    std::string Name() { return name; }
    QWidget* Editor() { return editor; }

private:
    std::string name;
    std::string fullPath;
    bool changed;

    QWidget* editor;
};
