
#pragma once

#include "TextDocument.h"

class LuaDocument : public TextDocument
{
public:
    LuaDocument(Path documentPath);

    virtual DocumentType getType() const override;
};
