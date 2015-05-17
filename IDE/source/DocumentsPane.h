
#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QMessageBox>
#include <string>
#include "Document.h"


class DocumentsPane : public QTabWidget
{
    Q_OBJECT

public:
    DocumentsPane();

    void Open(std::string path);
    Document* GetCurrentDocument();
    Document* GetDocument(int index);

    void SaveCurrentDocument();
    void CheckOutsideModification();

private:
    int ReloadDocumentMessageBox(Document* document);

private slots:
    void CloseTab(int index);
    void UpdateTabNames();
};
