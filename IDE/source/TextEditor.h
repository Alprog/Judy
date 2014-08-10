
#pragma once

#include "Document.h"
#include "../qt/ScintillaEdit.h"

#include "SciLexer.h"
#include "string"

class TextEditor : public ScintillaEdit
{
public:
    TextEditor();

private:
    void init();


};
