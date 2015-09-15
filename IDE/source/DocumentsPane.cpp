
#include "DocumentsPane.h"

#include <QTabBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QRadioButton>
#include <QResizeEvent>
#include <QTableWidget>
#include <string>

#include "Document.h"

DocumentsPane::DocumentsPane()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));
}

void DocumentsPane::Open(std::string path)
{
    for (int i = 0; i < count(); i++)
    {
        auto document = GetDocument(i);
        if (document->GetFullPath() == path)
        {
            setCurrentWidget(document);
            return;
        }
    }

    auto document = new DocumentM(path);
    connect(document, SIGNAL(Modified()), this, SLOT(UpdateTabNames()));
    addTab(document, document->GetName().c_str());
    this->setCurrentWidget(document);
}

void DocumentsPane::OpenAtLine(std::string path, int line)
{
    Open(path);
    GetCurrentDocument()->GoToLine(line);
}

DocumentM* DocumentsPane::GetDocument(int index)
{
    return (DocumentM*)widget(index);
}

DocumentM* DocumentsPane::GetCurrentDocument()
{
    return (DocumentM*)widget(currentIndex());
}

void DocumentsPane::SaveCurrentDocument()
{
    if (count() > 0)
    {
        GetCurrentDocument()->Save();
    }
}

void DocumentsPane::UpdateTabNames()
{
    for (int i = 0; i < count(); i++)
    {
        auto document = (DocumentM*)widget(i);
        auto name = document->GetTabName();
        this->setTabText(i, name.c_str());
    }
}

void DocumentsPane::CheckOutsideModification()
{
    bool toAll = false;
    bool reload = false;

    for (int i = 0; i < count(); i++)
    {
        auto document = (DocumentM*)widget(i);
        if (document->IsModifiedOutside())
        {
            if (!toAll)
            {
                setCurrentWidget(document);
                int result = ReloadDocumentMessageBox(document);
                reload = (result == QMessageBox::Yes) || (result == QMessageBox::YesToAll);
                toAll = (result == QMessageBox::YesToAll) || (result == QMessageBox::NoToAll);
            }

            if (reload)
            {
                document->Reload();
            }
            else
            {
                document->IgnoreOutsideModification();
            }
        }
    }
}

int DocumentsPane::ReloadDocumentMessageBox(DocumentM* document)
{
    QMessageBox msgBox;
    msgBox.setText(document->GetName().c_str());

    auto text = "This file has been modified by another program.\n"
                "Do you want to reload it?";
    msgBox.setInformativeText(text);

    auto buttons = QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll;
    msgBox.setStandardButtons(buttons);

    return msgBox.exec();
}

void DocumentsPane::CloseTab(int index)
{
    auto document = GetDocument(index);

    if (document->HaveChanges())
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
                document->Save();
                break;

            case QMessageBox::Cancel:
                return;
        }
    }

    removeTab(index);
}
