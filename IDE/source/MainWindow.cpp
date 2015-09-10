
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

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setObjectName("fileToolBar");
    fileToolBar->setIconSize(QSize(20, 20));

    QAction* fileActions[]
    {
        createAction("New", "new", SLOT(newFile()), QKeySequence::New),
        createAction("Open", "open", SLOT(openFile()), QKeySequence::Open),
        createAction("Save", "save", SLOT(saveFile()), QKeySequence::Save),
        createAction("Save As", "", SLOT(saveAsFile()), QKeySequence::SaveAs)
    };

    for (QAction* action : fileActions)
    {
        fileMenu->addAction(action);
        if (!action->icon().isNull())
        {
            fileToolBar->addAction(action);
        }
    }

    //---------------

    debugMenu = new DebugMenu();

    debugToolBar = addToolBar(tr("Debug"));
    debugToolBar->setObjectName("debugToolBar");
    debugToolBar->setIconSize(QSize(20, 20));

//    for (auto action : debugActions)
//    {
//        debugToolBar->addAction(action);
//    }

    menuBar()->addMenu(debugMenu);

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

QByteArray ba;

void MainWindow::newFile()
{
    this->restoreState(ba, 0);
}

void MainWindow::openFile()
{
    auto filter = tr("Any supported (*.lua *.hlsl *.scene);;Lua (*.lua);;HLSL (*.hlsl);;Scene (*.scene)");
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", filter);
    if (!fileName.isEmpty())
    {
        documents->Open(fileName.toUtf8().constData());
    }
}

void MainWindow::saveFile()
{
    documents->SaveCurrentDocument();
}

void MainWindow::saveAsFile()
{
    printf("save!\n");
    ba = this->saveState(0);
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

void MainWindow::startDebug()
{
    RemotePlayer::Instance()->Run();

//    auto machine = LuaMachine::Instance();
//    if (machine->IsStarted())
//    {
//        machine->Continue();
//    }
//    else
//    {
//        machine->Start("main.lua");
//    }
}

void MainWindow::stopDebug()
{
    RemotePlayer::Instance()->Stop();
}
