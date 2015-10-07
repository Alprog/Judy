
#pragma once

#include "Document.h"

class LuaDocument : public DocumentM
{
public:
    LuaDocument::LuaDocument(Path documentPath);

private:
    virtual QByteArray GetTextData() override;
};
