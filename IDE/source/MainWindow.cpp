
#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QEvent>
#include "OutputPane.h"
#include "LuaMachine/LuaMachine.h"

#include "DocumentsPane.h"
#include "../qt/ScintillaEditBase.h"

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
    dockWidget = new QDockWidget("Dock2", 0, 0);
    dockWidget->setObjectName("Dock2");
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    documents = new DocumentsPane;
    setCentralWidget(documents);
}

QAction* MainWindow::createAction(const char* name, const char* icon, const char* slot, const QKeySequence& shortcut)
{
    auto action = new QAction(tr(name), this);
    if (icon != nullptr)
    {
        action->setIcon(QIcon(icon));
    }

    action->setShortcut(shortcut);
    connect(action, SIGNAL(triggered()), this, slot);
    return action;
}

#include <iostream>

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->setObjectName("fileToolBar");
    fileToolBar->setIconSize(QSize(20, 20));

    QAction* fileActions[]
    {
        createAction("New", ":/images/new.png", SLOT(newFile()), QKeySequence::New),
        createAction("Open", ":/images/open.png", SLOT(openFile()), QKeySequence::Open),
        createAction("Save", ":/images/save.png", SLOT(saveFile()), QKeySequence::Save),
        createAction("Save As", nullptr, SLOT(saveAsFile()), QKeySequence::SaveAs)
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

    debugMenu = menuBar()->addMenu(tr("&Debug"));
    debugToolBar = addToolBar(tr("Debug"));
    debugToolBar->setObjectName("debugToolBar");
    debugToolBar->setIconSize(QSize(20, 20));

    QAction* debugActions[]
    {
        createAction("Start", ":/images/play.png", SLOT(startDebug()), Qt::Key_F5),
        createAction("Break", ":/images/pause.png", SLOT(stopDebug()), Qt::Key_F6),
        createAction("Step Into", ":/images/stepinto.png", SLOT(saveAsFile()), Qt::Key_F11),
        createAction("Step Over", ":/images/stepover.png", SLOT(saveAsFile()), Qt::Key_F10),
        createAction("Step Out", ":/images/stepout.png", SLOT(saveAsFile()), QKeySequence(Qt::SHIFT + Qt::Key_F11))
    };

    for (auto action : debugActions)
    {
        debugMenu->addAction(action);
        debugToolBar->addAction(action);
    }

    //---------------

    auto windowMenu = menuBar()->addMenu(tr("&Window"));
    auto layoutMenu = windowMenu->addMenu(tr("&Layout"));
    for (int i = 0; i < 4; i++)
    {
        auto str = std::to_string(i);
        auto name = str.c_str();
        createAction(name, nullptr, SLOT(saveAsFile()));
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
    auto machine = LuaMachine::Instance();
    if (machine->IsStarted())
    {
        machine->Continue();
    }
    else
    {
        machine->Start("main.lua");
    }
}

void MainWindow::stopDebug()
{
    LuaMachine::Instance()->Stop();
}
