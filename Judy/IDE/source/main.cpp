
#include "../../../3rd-Party/scintilla/qt/ScintillaEditBase.h"
#include "../../../3rd-Party/scintilla/qt/ScintillaEdit.h"
#include "SciLexer.h"

#define Window W
#include "App.h"
#define Window Window

#include <QApplication>
#include <QWidget>

#include <QMainWindow>

const char g_cppKeyWords[] =
    "and break do else elseif end "
    "false for function goto if in "
    " nil not or repeat return "
    "then true until while ";

const char g_cppKeyWords2[] = "local";

int RGB(int r, int g, int b)
{
    return r | g << 8 | b << 16;
}

const int black = RGB( 0, 0, 0 );
const int white = RGB( 255, 255, 255 );
const int green = RGB( 0, 100, 0 );
const int red = RGB( 255, 0, 0 );
const int yellow = RGB( 255, 255, 0 );
const int magenta = RGB( 255, 0, 255 );
const int blue = RGB( 0, 0, 255 );
const int darkblue = RGB( 0, 0, 150 );

/// Default color scheme
int colors[20][2] =
{
    { SCE_LUA_DEFAULT, black },
    { SCE_LUA_COMMENT, green },
    { SCE_LUA_COMMENTLINE, green },
    { SCE_LUA_COMMENTDOC, green },
    { SCE_LUA_NUMBER, red },
    { SCE_LUA_WORD, blue },
    { SCE_LUA_STRING, red },
    { SCE_LUA_CHARACTER, red },
    { SCE_LUA_LITERALSTRING, red },
    { SCE_LUA_PREPROCESSOR, black },
    { SCE_LUA_OPERATOR, darkblue },
    { SCE_LUA_IDENTIFIER, black },
    { SCE_LUA_STRINGEOL, green },
    { SCE_LUA_WORD2, blue },
    { SCE_LUA_WORD3, green },
    { SCE_LUA_WORD4, green },
    { SCE_LUA_WORD5, green },
    { SCE_LUA_WORD6, green },
    { SCE_LUA_WORD7, green },
    { SCE_LUA_WORD8, green }
};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(600, 600);
    window.setWindowTitle("Judy");


    ScintillaEdit edit(&window);
    edit.resize(600, 600);

    //edit.setStyleBits(5);
    edit.setTabWidth(4);

    edit.setLexer(SCLEX_LUA);
    edit.setKeyWords(0, g_cppKeyWords);
    edit.setKeyWords(1, g_cppKeyWords2);


    edit.styleSetFont(STYLE_DEFAULT, "Courier New");
    edit.styleSetSize(STYLE_DEFAULT, 12);
    edit.styleClearAll();
    for(int i = 0; i < 20; i++)
    {
        edit.styleSetFore(colors[i][0], colors[i][1]);
    }

    edit.styleSetSize(STYLE_LINENUMBER, 10);


    //edit.styleSetFore(STYLE_DEFAULT, green);

    edit.setText("local a = 4; -- bla\nfunction a()\n   local b\nend\n--[[\nefjejg\n]]");
    edit.setProperty("fold", "1");
    edit.setProperty("fold.compact", "0");

    edit.setProperty("fold.comment", "1");
    edit.setProperty("fold.preprocessor", "1");

    int INDEX = 2;
    edit.setMarginWidthN(INDEX, 0);

    edit.setMarginTypeN(INDEX, SC_MARGIN_SYMBOL);
    edit.setMarginMaskN(INDEX, SC_MASK_FOLDERS);
    edit.setMarginWidthN(INDEX, 15);
    edit.setMarginSensitiveN(INDEX, true);

    edit.setAutomaticFold(SC_AUTOMATICFOLD_SHOW | SC_AUTOMATICFOLD_CLICK);


    edit.setMarginWidthN(0, 40);

    edit.markerDefine(SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
    edit.markerDefine(SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);

    edit.markerDefine(SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
    edit.markerDefine(SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
    edit.markerDefine(SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
    edit.markerDefine(SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
    edit.markerDefine(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);




    //int lid = edit.lexer();
    //

    //edit.colourise(0, -1);


    /*edit.setText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (int i = 0; i < 30; i++)
    {
        edit.markerDefine(i, i );
        edit.markerSetFore(i, 200 << 8);
        edit.markerSetBack(i, 200);
        edit.markerAdd(i, i);
    }*/

    //int color = 0 | (200 << 8) | (0 << 16);
    //edit.setSelBack(true, color);


    //window.showMaximized();
    window.show();


    int a = window.winId();

    printf("%i", a);
    fflush(stdout);

    return app.exec();

}
