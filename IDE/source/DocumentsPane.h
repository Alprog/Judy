
#pragma once

#include "QWidget.h"
#include "QTabWidget.h"
#include "string"
#include "Document.h"

class DocumentsPane : public QTabWidget
{
    Q_OBJECT

public:
    DocumentsPane();

    void Add(std::string fileName);
    Document* GetCurrentDocument();
    Document* GetDocument(int index);

    void SaveCurrentDocument();

private slots:
    void CloseTab(int index);
    void UpdateTabNames();
};
