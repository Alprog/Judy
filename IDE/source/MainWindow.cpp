
#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QEvent>
#include "DocumentsPane.h"
#include "TextEditor.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , modificationChecking(false)
{
    setWindowTitle("Judy IDE");

    setWindowIcon(QIcon(":/images/icon.png"));

    setWindowOpacity(1);

    createActions();

    this->installEventFilter(this);
}

QAction* MainWindow::createAction(const char* name, const char* icon, const char* slot, QKeySequence::StandardKey shortcut)
{
    auto action = new QAction(QIcon(icon), tr(name), this);
    action->setShortcuts(shortcut);
    connect(action, SIGNAL(triggered()), this, slot);
    return action;
}

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));

    QAction* actions[]
    {
        createAction("&New", ":/images/new.png", SLOT(newFile()), QKeySequence::New),
        createAction("&Open", ":/images/open.png", SLOT(openFile()), QKeySequence::Open),
        createAction("&Save", ":/images/save.png", SLOT(saveFile()), QKeySequence::Save),
        createAction("&SaveAs", NULL, SLOT(saveAsFile()), QKeySequence::SaveAs)
    };

    for (auto action : actions)
    {
        fileMenu->addAction(action);
        fileToolBar->addAction(action);
    }

    QDockWidget* dockWidget;

    dockWidget = new QDockWidget("Dock", 0, 0);

    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    documents = new DocumentsPane;
    setCentralWidget(documents);
}

void MainWindow::newFile()
{

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
