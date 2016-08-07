
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

    void Open(Path path);
    void OpenAtLine(Path path, int line);
    IDocument* GetCurrentDocument();
    IDocument* GetDocument(Path path);
    IDocument* GetDocument(int index);

    void SaveCurrentDocument();
    void CheckOutsideModification();

private:
    static IDocument* CreateDocument(Path absolutePath);
    int ReloadDocumentMessageBox(IDocument* document);

private slots:
    void CloseTab(int index);
    void UpdateTabNames();
};
