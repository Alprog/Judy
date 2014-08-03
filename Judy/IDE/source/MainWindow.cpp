
#include "MainWindow.h"
#include "QAction.h"
#include "QMenuBar.h"
#include "QToolBar.h"
#include "QDockWidget"
#include "TextEditor.h"
#include "QFileDialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Judy IDE");

    setWindowIcon(QIcon(":/images/icon.png"));

    setWindowOpacity(1);

    createActions();
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

    auto tabs = new QTabWidget;

    tabs->setTabsClosable(true);
    tabs->setMovable(true);

    tabs->addTab(new TextEditor, "Ololo");
    tabs->addTab(new TextEditor, "Ololo");

    setCentralWidget(tabs);
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{
    auto filter = tr("Any supported (*.lua *.hlsl *.scene);;Lua (*.lua);;HLSL (*.hlsl);;Scene (*.scene)");
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", filter);

}

void MainWindow::saveFile()
{

}

void MainWindow::saveAsFile()
{

}
