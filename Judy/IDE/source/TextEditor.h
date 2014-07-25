
#pragma once

#include "../qt/ScintillaEdit.h"
#include "SciLexer.h"

class TextEditor : public ScintillaEdit
{
public:
    TextEditor();
    TextEditor(QWidget* parent);

private:
    void init();
};
