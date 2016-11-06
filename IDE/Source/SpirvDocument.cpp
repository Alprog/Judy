
#include "SpirvDocument.h"
#include "CrossCompiler/CrossCompiler.h"

void SpirvDocument::setBinaryData(QByteArray binaryData)
{
    this->binaryData = binaryData;

    auto text = CrossCompiler::getInstance()->SpirvToHumanReadable(binaryData);
    this->setText(text);
}

QByteArray SpirvDocument::getBinaryData() const
{
    return binaryData;
}
