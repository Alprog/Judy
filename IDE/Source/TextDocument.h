
#pragma once

#include "Document.h"
#include "CodeEditor.h"

class TextDocument : public IDocument
{
public:
    TextDocument(std::string documentPath, CodeEditor::HighlightType highlightType = CodeEditor::HighlightType::None);

    virtual DocumentType getType() const override;
    virtual void save() override;
    virtual bool changed() const override;
    void goToLine(int line);

protected:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() override;

    CodeEditor* editor;
};
