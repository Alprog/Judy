
#include "HlslDocument.h"
#include "CodeEditor.h"
#include <QLayout>
#include <QTabWidget>
#include "CrossCompiler/CrossCompiler.h"

HlslDocument::HlslDocument()
    : TextDocument(CodeEditor::HighlightType::HLSL)
{
    spirvDocument = new SpirvDocument();
    glslDocument = new TextDocument();

    auto tabPanel = new QTabWidget();
    tabPanel->setTabPosition(QTabWidget::South);
    tabPanel->addTab(editor, "HLSL");
    tabPanel->addTab(spirvDocument, "SPIRV");
    tabPanel->addTab(glslDocument, "GLSL");

    auto layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 5);
    layout->addWidget(tabPanel);
    delete this->layout();
    this->setLayout(layout);
}

DocumentType HlslDocument::getType() const
{
    return DocumentType::Hlsl;
}

void HlslDocument::save()
{
    TextDocument::save();

    auto compiler = CrossCompiler::getInstance();

    auto hlslText = this->getText();

    auto spirvBinary = compiler->HlslToSpirv(hlslText);
    spirvDocument->setBinaryData(spirvBinary);
    spirvDocument->save();

    auto glslText = compiler->SpirvToGlsl(spirvBinary);
    glslDocument->setText(glslText);
    glslDocument->save();
}

void HlslDocument::reload()
{
    TextDocument::reload();

    auto directoryPath = documentPath.getParentPath();
    auto baseName = documentPath.getNameWithoutExtension();

    auto spirvPath = Path::combine(directoryPath, baseName + ".spirv");
    spirvDocument->open(spirvPath);
    spirvDocument->setReadOnly(true);

    auto glslPath = Path::combine(directoryPath, baseName + ".glsl");
    glslDocument->open(glslPath);
    glslDocument->setReadOnly(true);
}
