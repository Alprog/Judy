
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
    DocumentM* GetCurrentDocument();
    DocumentM* GetDocument(int index);

    void SaveCurrentDocument();
    void CheckOutsideModification();

private:
    int ReloadDocumentMessageBox(DocumentM* document);

private slots:
    void CloseTab(int index);
    void UpdateTabNames();
};
