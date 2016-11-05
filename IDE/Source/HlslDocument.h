
#pragma once

#include "TextDocument.h"

class HlslDocument : public TextDocument
{
public:
    HlslDocument(std::string documentPath);

    virtual DocumentType getType() const override;
};
