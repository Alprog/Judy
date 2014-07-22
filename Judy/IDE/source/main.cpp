
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

    // Standard
    "asm auto bool break case catch char class const "
    "const_cast continue default delete do double "
    "dynamic_cast else enum explicit extern false finally "
    "float for friend goto if inline int long mutable "
    "namespace new operator private protected public "
    "register reinterpret_cast register return short signed "
    "sizeof static static_cast struct switch template "
    "this throw true try typedef typeid typename "
    "union unsigned using virtual void volatile "
    "wchar_t while "

    // Extended
    "__asm __asume __based __box __cdecl __declspec "
    "__delegate delegate depreciated dllexport dllimport "
    "event __event __except __fastcall __finally __forceinline "
    "__int8 __int16 __int32 __int64 __int128 __interface "
    "interface __leave naked noinline __noop noreturn "
    "nothrow novtable nullptr safecast __stdcall "
    "__try __except __finally __unaligned uuid __uuidof "
    "__virtual_inheritance";

int RGB(int r, int g, int b)
{
    return r | g << 8 | b << 16;
}

const int black = RGB( 0, 0, 0 );
const int white = RGB( 255, 255, 255 );
const int green = RGB( 0, 255, 0 );
const int red = RGB( 255, 0, 0 );
const int blue = RGB( 0, 0, 255 );
const int yellow = RGB( 255, 255, 0 );
const int magenta = RGB( 255, 0, 255 );
const int cyan = RGB( 0, 255, 255 );

/// Default color scheme
int colors[10][2] =
{
    {   SCE_C_COMMENT,          green },
    {   SCE_C_COMMENTLINE,      green },
    {   SCE_C_COMMENTDOC,       green },
    {   SCE_C_NUMBER,           magenta },
    {   SCE_C_STRING,           yellow },
    {   SCE_C_CHARACTER,        yellow },
    {   SCE_C_UUID,             cyan },
    {   SCE_C_OPERATOR,         red },
    {   SCE_C_PREPROCESSOR,     cyan },
    {   SCE_C_WORD,             cyan },
};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(600, 600);
    window.setWindowTitle("Judy");


    ScintillaEdit edit(&window);
    edit.resize(600, 600);

    edit.setStyleBits(5);
    edit.setTabWidth(4);

    edit.setLexer(SCLEX_CPP);
    edit.setKeyWords(0, g_cppKeyWords);
    for(int i = 0; i < 10; i++)
    {
        edit.styleSetFore(colors[i][0], colors[i][1]);
    }

    edit.styleSetFont(STYLE_DEFAULT, "Courier New");
    edit.styleSetSize(STYLE_DEFAULT, 15);

    edit.setText("int a = 4; // bla");

    //int lid = edit.lexer();

    edit.colourise(0, -1);


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
    edit.styleClearAll();

    //window.showMaximized();
    window.show();


    int a = window.winId();

    printf("%i", a);
    fflush(stdout);

    return app.exec();

}
