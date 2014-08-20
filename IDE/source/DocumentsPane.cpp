
#include "DocumentsPane.h"
#include "Document.h"

#include "QTabBar.h"
#include "QTextEdit"

#include "QVBoxLayout"
#include "QScrollArea"
#include "QRadioButton"
#include "QResizeEvent"

DocumentsPane::DocumentsPane()
{
    auto vbox = new QVBoxLayout(this);
    vbox->setMargin(0);
    vbox->setSpacing(0);

    auto bar = new QTabBar(this);

    bar->addTab("fef");
    bar->addTab("fef");

    bar->setExpanding(false);
    bar->setMovable(true);

    auto editor = new QWidget();

    vbox->addWidget(bar);
    vbox->addWidget(editor);

    this->setLayout(vbox);


    /*setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);


    auto document = new Document;
    addTab(document->Editor(), document->Name().c_str());

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(CloseTab(int)));*/
}

void DocumentsPane::Add(std::string fileName)
{
    /*auto document = new Document(fileName);
    addTab(document->Editor(), document->Name().c_str());
    this->setCurrentWidget(document->Editor());*/
}

void DocumentsPane::CloseTab(int index)
{
    //removeTab(index);
}

void DocumentsPane::resizeEvent(QResizeEvent* event)
{
   int w = event->oldSize().width();
   int ww = event->size().width();

   QWidget::resizeEvent(event);
}
