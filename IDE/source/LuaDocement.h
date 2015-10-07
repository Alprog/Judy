
#pragma once

#include "Document.h"

class LuaDocument : public IDocument
{
public:
    LuaDocument::LuaDocument(Path documentPath);

private:
    virtual QByteArray GetTextData() override;
};
