
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

    void open(Path path);
    void openAtLine(Path path, int line);
    IDocument* getCurrentDocument();
    IDocument* getDocument(Path path);
    IDocument* getDocument(int index);

    void createNewScene();
    void saveCurrentDocument();
    void checkOutsideModification();

private:
    static IDocument* createDocumentByExtension(std::string extension);
    int reloadDocumentMessageBox(IDocument* document);

private slots:
    void closeTab(int index);
    void updateTabNames();
};
