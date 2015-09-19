
#include "FileMenu.h"
#include <QFileDialog>

FileMenu::FileMenu(MainWindow* window)
    : BaseMenu{"File", window}
{
    QList<QAction*> actions
    {
        createAction("New", "new", SLOT(NewFile()), QKeySequence::New),
        createAction("Open", "open", SLOT(OpenFile()), QKeySequence::Open),
        createAction("Save", "save", SLOT(SaveFile()), QKeySequence::Save),
        createAction("Save As", "", SLOT(SaveAsFile()), QKeySequence::SaveAs)
    };
    addActions(actions);
}

void FileMenu::NewFile()
{
}

void FileMenu::OpenFile()
{
    auto filter = tr("Any supported (*.lua *.hlsl *.scene);;Lua (*.lua);;HLSL (*.hlsl);;Scene (*.scene)");
    auto fileName = QFileDialog::getOpenFileName(window, tr("Open File"), "", filter);
    if (!fileName.isEmpty())
    {
        window->documents->Open(fileName.toUtf8().constData());
    }
}

void FileMenu::SaveFile()
{
    window->documents->SaveCurrentDocument();
}

void FileMenu::SaveAsFile()
{
}
