
#pragma once

#include "Document.h"
#include "SciLexer.h"
#include "../qt/ScintillaEdit.h"
#include "string"

class TextEditor : public ScintillaEdit
{
    Q_OBJECT

public:
    TextEditor(QWidget* parent = 0);
    void setSource(std::string source);

    void getBreakpointLines();

private slots:
    void onMarginClicked(int position, int modifiers, int margin);
    void onLinesAdded(int arg);
    void onDwellStart(int x, int y);

private:
    void init();

    std::string source;
};
