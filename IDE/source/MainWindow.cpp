
#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QEvent>
#include "OutputPane.h"

#include "RemotePlayer.h"

#include "DocumentsPane.h"
#include "../qt/ScintillaEditBase.h"
#include <iostream>
#include "Utils.h"

#include "Menu/DebugMenu.h"
#include "Menu/FileMenu.h"

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


    auto area = Qt::BottomDockWidgetArea;
    addDockWidget(area, new OutputPane());


    QDockWidget* dockWidget;
    dockWidget = new QDockWidget("Stack", 0, 0);
    dockWidget->setObjectName("Stack");
    dockWidget->setMinimumWidth(250);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    documents = new DocumentsPane;
    setCentralWidget(documents);
}

MainWindow::~MainWindow()
{
    delete debugMenu;
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
    fileMenu = new FileMenu();
    menuBar()->addMenu(fileMenu);
    createToolBar(fileMenu);

    //---------------

    debugMenu = new DebugMenu();
    menuBar()->addMenu(debugMenu);
    createToolBar(debugMenu);

    //---------------

    auto windowMenu = menuBar()->addMenu(tr("&Window"));
    auto layoutMenu = windowMenu->addMenu(tr("&Layout"));
    for (int i = 0; i < 4; i++)
    {
        auto str = std::to_string(i);
        auto name = str.c_str();
        createAction(name, "", SLOT(saveAsFile()));
        layoutMenu->addAction(tr(name));
    }
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
