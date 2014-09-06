
#pragma once

#include "Document.h"
#include "../qt/ScintillaEdit.h"
#include "SciLexer.h"
#include "string"

class TextEditor : public ScintillaEdit
{
public:
    TextEditor(QWidget* parent = 0);

private:
    void init();
};
