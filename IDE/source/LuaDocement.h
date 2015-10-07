
#pragma once

#include "Document.h"

class CodeEditor;

class LuaDocument : public IDocument
{
public:
    LuaDocument::LuaDocument(Path documentPath);

    virtual void Save() override;
    virtual bool Changed() override;
    void GoToLine(int line);

private:
    virtual void SetBinaryData(QByteArray data) override;
    virtual QByteArray GetBinaryData() override;

    CodeEditor* editor;
};
