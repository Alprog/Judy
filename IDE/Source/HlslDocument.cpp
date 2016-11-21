
#include "HlslDocument.h"
#include "CodeEditor.h"
#include <QLayout>
#include <QTabWidget>
#include "CrossCompiler/CrossCompiler.h"

HlslDocument::HlslDocument()
    : TextDocument(CodeEditor::HighlightType::HLSL)
{
    vsSpirvDocument = new SpirvDocument();
    psSpirvDocument = new SpirvDocument();
    vsGlslDocument = new TextDocument();
    psGlslDocument = new TextDocument();

    auto tabPanel = new QTabWidget();
    tabPanel->setTabPosition(QTabWidget::South);
    tabPanel->addTab(editor, "HLSL");
    tabPanel->addTab(vsSpirvDocument, "SPIRV VS");
    tabPanel->addTab(psSpirvDocument, "SPIRV PS");
    tabPanel->addTab(vsGlslDocument, "GLSL VS");
    tabPanel->addTab(psGlslDocument, "GLSL PS");

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

    try
    {
        auto spirvBinary = compiler->hlslToSpirv(hlslText);
        if (spirvBinary.vs.size() > 0)
        {
            vsSpirvDocument->setBinaryData(spirvBinary.vs);
            vsSpirvDocument->save();

            auto glslText = compiler->spirvToGlsl(spirvBinary.vs);
            vsGlslDocument->setText(glslText);
            vsGlslDocument->save();
        }
        if (spirvBinary.ps.size() > 0)
        {
            psSpirvDocument->setBinaryData(spirvBinary.ps);
            psSpirvDocument->save();

            auto glslText = compiler->spirvToGlsl(spirvBinary.ps);
            psGlslDocument->setText(glslText);
            psGlslDocument->save();
        }
    }
    catch (std::exception exeption)
    {
        printf("%s\n", exeption.what());
    }
}

void HlslDocument::reload()
{
    TextDocument::reload();

    auto directoryPath = documentPath.getParentPath() + "gen";
    auto baseName = documentPath.getNameWithoutExtension();

    auto vsSpirvPath = Path::combine(directoryPath, baseName + ".vs.spirv");
    vsSpirvDocument->open(vsSpirvPath);
    vsSpirvDocument->setReadOnly(true);

    auto psSpirvPath = Path::combine(directoryPath, baseName + ".ps.spirv");
    psSpirvDocument->open(psSpirvPath);
    psSpirvDocument->setReadOnly(true);

    auto vsGlslPath = Path::combine(directoryPath, baseName + ".vs.glsl");
    vsGlslDocument->open(vsGlslPath);
    vsGlslDocument->setReadOnly(true);

    auto psGlslPath = Path::combine(directoryPath, baseName + ".ps.glsl");
    psGlslDocument->open(psGlslPath);
    psGlslDocument->setReadOnly(true);
}
