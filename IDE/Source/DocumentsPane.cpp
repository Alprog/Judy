
#include "DocumentsPane.h"

#include <QTabBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QResizeEvent>
#include <QTableWidget>
#include <string>
#include "Utils.h"
#include "LuaDocument.h"
#include "HlslDocument.h"
#include "SceneDocument.h"

#include "IDE.h"

DocumentsPane::DocumentsPane()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);
    setObjectName("documentsTabs");
    tabBar()->setObjectName("documentsTabs");

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

void DocumentsPane::open(Path path)
{
    if (!path.isAbsolute())
    {
        path = Path::combine(IDE::getInstance()->settings.projectPath, path);
    }

    auto document = getDocument(path);
    if (document != nullptr)
    {
        setCurrentWidget(document);
    }
    else
    {
        auto extension = path.getExtension();
        document = createDocumentByExtension(extension);
        if (document != nullptr)
        {
            document->open(path);
            connect(document, SIGNAL(modified()), this, SLOT(updateTabNames()));
            addTab(document, document->getName().c_str());
            setCurrentWidget(document);
        }
    }
}

IDocument* DocumentsPane::createDocumentByExtension(std::string extension)
{
    extension = lowerCase(extension);
    if (extension == "lua")
    {
        return new LuaDocument();
    }
    else if (extension == "hlsl")
    {
        return new HlslDocument();
    }
    else if (extension == "scene")
    {
        return new SceneDocument();
    }
    else
    {
        return nullptr;
    }
}

void DocumentsPane::openAtLine(Path path, int line)
{
    open(path);
    auto document = getCurrentDocument();
    if (document->getType() == DocumentType::Lua)
    {
        static_cast<LuaDocument*>(document)->goToLine(line);
    }
}

IDocument* DocumentsPane::getDocument(Path path)
{
#if WIN
    const bool caseSensitive = false;
#else
    const bool caseSensitive = true;
#endif
    for (int i = 0; i < count(); i++)
    {
        auto document = getDocument(i);
        if (Path::isEqual(document->getPath(), path, caseSensitive))
        {
            return document;
        }
    }
    return nullptr;
}

IDocument* DocumentsPane::getDocument(int index)
{
    return (IDocument*)widget(index);
}

IDocument* DocumentsPane::getCurrentDocument()
{
    return (IDocument*)widget(currentIndex());
}

void DocumentsPane::createNewScene()
{
    open("newDocument.scene");
}

void DocumentsPane::saveCurrentDocument()
{
    if (count() > 0)
    {
        getCurrentDocument()->save();
    }
}

void DocumentsPane::updateTabNames()
{
    for (int i = 0; i < count(); i++)
    {
        auto document = (IDocument*)widget(i);
        auto name = document->getTabName();
        this->setTabText(i, name.c_str());
    }
}

void DocumentsPane::checkOutsideModification()
{
    bool toAll = false;
    bool reload = false;

    for (int i = 0; i < count(); i++)
    {
        auto document = getDocument(i);
        if (document->isModifiedOutside())
        {
            if (!toAll)
            {
                setCurrentWidget(document);
                int result = reloadDocumentMessageBox(document);
                reload = (result == QMessageBox::Yes) || (result == QMessageBox::YesToAll);
                toAll = (result == QMessageBox::YesToAll) || (result == QMessageBox::NoToAll);
            }

            if (reload)
            {
                document->reload();
            }
            else
            {
                document->ignoreOutsideModification();
            }
        }
    }
}

int DocumentsPane::reloadDocumentMessageBox(IDocument* document)
{
    QMessageBox msgBox;
    msgBox.setText(document->getName().c_str());

    auto text = "This file has been modified by another program.\n"
                "Do you want to reload it?";
    msgBox.setInformativeText(text);

    auto buttons = QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll;
    msgBox.setStandardButtons(buttons);

    return msgBox.exec();
}

void DocumentsPane::closeTab(int index)
{
    auto document = getDocument(index);

    if (document->changed())
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int result = msgBox.exec();

        switch (result)
        {
            case QMessageBox::Save:
                document->save();
                break;

            case QMessageBox::Cancel:
                return;
        }
    }

    removeTab(index);
}
