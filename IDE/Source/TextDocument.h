
#pragma once

#include "Document.h"
#include "CodeEditor.h"

class TextDocument : public IDocument
{
public:
    TextDocument(CodeEditor::HighlightType highlightType = CodeEditor::HighlightType::None);

    virtual DocumentType getType() const override;
    virtual void resave() override;
    virtual bool changed() const override;

    std::string getText() const;
    void setText(std::string text);
    void goToLine(int line);
    void setReadOnly(bool value);

protected:
    virtual void setBinaryData(QByteArray data) override;
    virtual QByteArray getBinaryData() const override;

    CodeEditor* editor;
};
