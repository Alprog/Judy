
#pragma once
#include <QMainWindow>
#include "DocumentsPane.h"
#include "LuaMachine/LuaMachine.h"

class DebugMenu;

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

    void startDebug();
    void stopDebug();

private:
    void createActions();

    bool eventFilter(QObject* obj, QEvent* event) override;

    QMenu* fileMenu;
    QToolBar* fileToolBar;

    DebugMenu* debugMenu;
    QToolBar* debugToolBar;

    QMenu* editMenu;


    DocumentsPane* documents;
    bool modificationChecking;

    LuaMachine* luaMachine;
};

