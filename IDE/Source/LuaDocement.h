
#pragma once

#include "Document.h"

class CodeEditor;

class LuaDocument : public IDocument
{
public:
    LuaDocument(Path documentPath);

    virtual DocumentType GetType() const override;

    virtual void Save() override;
    virtual bool Changed() const override;
    void GoToLine(int line);

private:
    virtual void SetBinaryData(QByteArray data) override;
    virtual QByteArray GetBinaryData() override;

    CodeEditor* editor;
};
