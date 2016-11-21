
#pragma once

#include "TextDocument.h"

class LuaDocument : public TextDocument
{
public:
    LuaDocument();

    virtual DocumentType getType() const override;
    virtual void reload() override;
};
