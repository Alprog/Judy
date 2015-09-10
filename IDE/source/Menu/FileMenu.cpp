
#include "FileMenu.h"

FileMenu::FileMenu()
    : BaseMenu{"File"}
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

//QByteArray ba;

void FileMenu::NewFile()
{
    //this->restoreState(ba, 0);
}

void FileMenu::OpenFile()
{
//    auto filter = tr("Any supported (*.lua *.hlsl *.scene);;Lua (*.lua);;HLSL (*.hlsl);;Scene (*.scene)");
//    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", filter);
//    if (!fileName.isEmpty())
//    {
//        documents->Open(fileName.toUtf8().constData());
//    }
}

void FileMenu::SaveFile()
{
//    documents->SaveCurrentDocument();
}

void FileMenu::SaveAsFile()
{
//    printf("save!\n");
//    ba = this->saveState(0);
}
