
#pragma once

#include "Document.h"

class CodeEditor;

class TextDocument : public IDocument
{
public:
    TextDocument(Path documentPath, std::string extension);

    virtual DocumentType getType() const override;
    std::string getText();

    virtual void save() override;
    virtual bool changed() const override;
    void goToLine(int line);

private:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() override;

    CodeEditor* editor;
};
