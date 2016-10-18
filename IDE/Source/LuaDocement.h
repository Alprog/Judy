
#pragma once

#include "Document.h"

class CodeEditor;

class LuaDocument : public IDocument
{
public:
    LuaDocument(Path documentPath);

    virtual DocumentType getType() const override;

    virtual void save() override;
    virtual bool changed() const override;
    void goToLine(int line);

private:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() override;

    CodeEditor* editor;
};
