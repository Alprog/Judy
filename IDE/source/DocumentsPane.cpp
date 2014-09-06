
#include "DocumentsPane.h"

#include "QTabBar.h"
#include "QTextEdit"

#include "QVBoxLayout"
#include "QScrollArea"
#include "QRadioButton"
#include "QResizeEvent"
#include "QTableWidget"
#include "string"

#include "QMessageBox.h"
#include "Document.h"

DocumentsPane::DocumentsPane()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));
}

void DocumentsPane::Add(std::string fileName)
{
    auto document = new Document(fileName);

    connect(document, SIGNAL(OnModified()), this, SLOT(UpdateTabNames()));

    addTab(document, document->Name().c_str());
    this->setCurrentWidget(document);
}

Document* DocumentsPane::GetDocument(int index)
{
    return (Document*)widget(index);
}

Document* DocumentsPane::GetCurrentDocument()
{
    return (Document*)widget(currentIndex());
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
        auto document = (Document*)widget(i);
        auto name = document->GetTabName();
        this->setTabText(i, name.c_str());
    }
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
