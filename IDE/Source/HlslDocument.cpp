
#include "HlslDocument.h"
#include "CodeEditor.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QPushButton>

HlslDocument::HlslDocument(std::string documentPath)
    : TextDocument{documentPath, CodeEditor::HighlightType::HLSL}
{
    auto tabPanel = new QTabWidget();
    tabPanel->setObjectName("bottomTabs");

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 5);
    layout->addWidget(tabPanel);
    delete this->layout();
    this->setLayout(layout);

    tabPanel->addTab(editor, "HLSL");
    tabPanel->addTab(new QWidget(), "GLSL");
    tabPanel->setTabPosition(QTabWidget::South);
}

DocumentType HlslDocument::getType() const
{
    return DocumentType::Hlsl;
}
