
#include "DocumentsControl.h"
#include "Document.h"

DocumentsControl::DocumentsControl()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);


    auto document = new Document;
    addTab(document->Editor(), document->Name().c_str());

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));
}

void DocumentsControl::Add(std::string fileName)
{
    auto document = new Document(fileName);
    addTab(document->Editor(), document->Name().c_str());
    this->setCurrentWidget(document->Editor());
}

void DocumentsControl::CloseTab(int index)
{
    removeTab(index);
}
