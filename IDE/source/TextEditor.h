
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

private:
    void init();
};
