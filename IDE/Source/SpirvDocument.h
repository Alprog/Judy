
#pragma once

#include "TextDocument.h"

class SpirvDocument : public TextDocument
{
    friend class HlslDocument;

protected:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() const override;

    QByteArray binaryData;
};
