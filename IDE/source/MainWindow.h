
#pragma once
#include <QMainWindow>
#include "DocumentsPane.h"
#include "LuaMachine/LuaMachine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    void createToolBar(QMenu* menu);
    void createActions();

    bool eventFilter(QObject* obj, QEvent* event) override;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* debugMenu;
    QMenu* windowMenu;

    DocumentsPane* documents;
    bool modificationChecking;

    LuaMachine* luaMachine;
};

