
#pragma once
#include <QMainWindow>

#include "DocumentsPane.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);


signals:

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();

private:
    void createActions();

    bool eventFilter(QObject* obj, QEvent* event) override;

    QAction* createAction(const char* name, const char* icon, const char* slot,
                          QKeySequence::StandardKey shortcut = QKeySequence::UnknownKey);

    QMenu* fileMenu;
    QToolBar* fileToolBar;

    QMenu* editMenu;


    DocumentsPane* documents;
    bool modificationChecking;
};
