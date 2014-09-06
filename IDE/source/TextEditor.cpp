
#include "TextEditor.h"
#include "QWidget.h"

int RGB(int r, int g, int b)
{
    return r | g << 8 | b << 16;
}

const int black = RGB( 0, 0, 0 );
const int white = RGB( 220, 220, 220 );
const int green = RGB( 87, 166, 74 );
const int red = RGB( 214, 156, 66 );
const int gray = RGB( 128, 128, 139 );
const int blue = RGB( 66, 156, 214 );
const int blueSelect = RGB(38, 79, 129);
const int darkBack = RGB(30, 30, 30);

TextEditor::TextEditor(QWidget* parent) : ScintillaEdit(parent)
{
    init();
}

void TextEditor::init()
{
    setTabWidth(4);

    setLexer(SCLEX_LUA);

    const char keyWords[] =
        "and break do else elseif end false for function goto if "
        "in nil not or repeat return require then true until while ";

    const char keyWords2[] = "local";

    setKeyWords(0, keyWords);
    setKeyWords(1, keyWords2);

    setCaretFore(white);

    styleSetFont(STYLE_DEFAULT, "Consolas");
    styleSetSize(STYLE_DEFAULT, 12);
    styleSetBack(STYLE_DEFAULT, darkBack);

    styleClearAll();


    setSelBack(true, blueSelect);

    int colors[20][2] =
    {
        { SCE_LUA_DEFAULT, white },
        { SCE_LUA_COMMENT, green },
        { SCE_LUA_COMMENTLINE, green },
        { SCE_LUA_COMMENTDOC, green },
        { SCE_LUA_NUMBER, red },
        { SCE_LUA_WORD, blue },
        { SCE_LUA_STRING, red },
        { SCE_LUA_CHARACTER, red },
        { SCE_LUA_LITERALSTRING, red },
        { SCE_LUA_PREPROCESSOR, white },
        { SCE_LUA_OPERATOR, gray },
        { SCE_LUA_IDENTIFIER, white },
        { SCE_LUA_STRINGEOL, green },
        { SCE_LUA_WORD2, blue },
        { SCE_LUA_WORD3, green },
        { SCE_LUA_WORD4, green },
        { SCE_LUA_WORD5, green },
        { SCE_LUA_WORD6, green },
        { SCE_LUA_WORD7, green },
        { SCE_LUA_WORD8, green }
    };

    for(int i = 0; i < 20; i++)
    {
        styleSetFore(colors[i][0], colors[i][1]);
    }

    styleSetSize(STYLE_LINENUMBER, 10);
    styleSetFore(STYLE_LINENUMBER, blue);
    styleSetBack(STYLE_LINENUMBER, darkBack);

    setProperty("fold", "1");
    setProperty("fold.compact", "0");

    setProperty("fold.comment", "1");
    setProperty("fold.preprocessor", "1");

    int INDEX = 2;
    setMarginWidthN(INDEX, 0);

    //marginSetStyle(1, STYLE_LINENUMBER);;

    setMarginTypeN(INDEX, SC_MARGIN_SYMBOL);
    setMarginMaskN(INDEX, SC_MASK_FOLDERS);
    setMarginWidthN(INDEX, 15);
    setMarginLeft(7);
    setMarginSensitiveN(INDEX, true);

    setAutomaticFold(SC_AUTOMATICFOLD_SHOW | SC_AUTOMATICFOLD_CLICK);

    setFoldMarginColour(true, darkBack);
    setFoldMarginHiColour(true, darkBack);

    setMarginWidthN(0, 40);
    markerDefine(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
    markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);

    markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
    markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
    markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
    markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
    markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);
}
