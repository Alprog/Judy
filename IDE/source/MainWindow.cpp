
#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QEvent>
#include "OutputPane.h"
#include "StackPane.h"
#include "InspectorPane.h"

#include "RemotePlayer.h"

#include "DocumentsPane.h"
#include "../qt/ScintillaEditBase.h"
#include <iostream>

#include "Menu/FileMenu.h"
#include "Menu/DebugMenu.h"
#include "Menu/WindowMenu.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , modificationChecking(false)
{
    setWindowTitle("Judy IDE");
    setWindowIcon(QIcon(":/images/icon.png"));
    setWindowOpacity(1);
    createActions();
    this->installEventFilter(this);

    this->setAnimated(true);
    this->setDockNestingEnabled(true);

    addDockWidget(Qt::BottomDockWidgetArea, new OutputPane());
    addDockWidget(Qt::RightDockWidgetArea, new StackPane());
    addDockWidget(Qt::LeftDockWidgetArea, new InspectorPane());

    documents = new DocumentsPane;
    setCentralWidget(documents);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar(QMenu* menu)
{
    auto toolBar = addToolBar(menu->title());
    toolBar->setObjectName(menu->title() + "ToolBar");
    toolBar->setIconSize(QSize(20, 20));
    for (auto& action : menu->actions())
    {
        if (!action->icon().isNull())
        {
            toolBar->addAction(action);
        }
    }
}

void MainWindow::createActions()
{
    fileMenu = new FileMenu(this);
    menuBar()->addMenu(fileMenu);
    createToolBar(fileMenu);

    debugMenu = new DebugMenu(this);
    menuBar()->addMenu(debugMenu);
    createToolBar(debugMenu);

    windowMenu = new WindowMenu(this);
    menuBar()->addMenu(windowMenu);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::WindowActivate)
    {
        if (!modificationChecking)
        {
            modificationChecking = true;
            documents->CheckOutsideModification();
            modificationChecking = false;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}
