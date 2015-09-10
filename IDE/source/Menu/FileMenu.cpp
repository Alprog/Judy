
#include "FileMenu.h"

FileMenu::FileMenu()
    : BaseMenu{"File"}
{
    addAction("New", "new", SLOT(NewFile()), QKeySequence::New);
    addAction("Open", "open", SLOT(OpenFile()), QKeySequence::Open);
    addAction("Save", "save", SLOT(SaveFile()), QKeySequence::Save);
    addAction("Save As", "", SLOT(SaveAsFile()), QKeySequence::SaveAs);
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
