
#pragma once

#include "TextDocument.h"
#include "SpirvDocument.h"

class HlslDocument : public TextDocument
{
public:
    HlslDocument();

    virtual DocumentType getType() const override;

    virtual void save() override;
    virtual void reload() override;

private:
    SpirvDocument* vsSpirvDocument;
    SpirvDocument* psSpirvDocument;
    TextDocument* vsGlslDocument;
    TextDocument* psGlslDocument;
};
