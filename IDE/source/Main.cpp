
#include "../../../3rd-Party/scintilla/qt/ScintillaEditBase.h"
#include "../../../3rd-Party/scintilla/qt/ScintillaEdit.h"
#include "SciLexer.h"

#define Window W
#include "App.h"
#define Window Window

#include <QApplication>
#include <QWidget>

#include <QMainWindow>
#include "QDockWidget"
#include "QTextEdit"
#include "QFile"
#include "MainWindow.h"
#include "QTextStream"

#include "iostream"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

void func(lua_State *L, lua_Debug *ar)
{
    printf("CALLED\n");

    lua_getstack(L, 0, ar);
    lua_getinfo(L, "nSl", ar);

    printf("%s\n", ar->what);
    printf("%s\n", ar->source);
    printf("%i\n", ar->currentline);

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();

    QFile file("style.css");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString sheet = stream.readAll();

        app.setStyleSheet(sheet);
    }



    /*lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_sethook(L, func, LUA_MASKLINE, 0);

    lua_pushnumber(L, 1.1);
    lua_setglobal(L, "cppvar");

    if (luaL_dofile(L, "luascript.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }*/
    /*if (lua_pcall(L, 0, LUA_MULTRET, 0))
    {
      std::cerr << "Something went wrong during execution" << std::endl;
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
    }*/

    /*lua_getglobal(L, "myluafunction");
    lua_pushnumber(L, 5);
    lua_pcall(L, 1, 1, 0);
    std::cout << "The return value of the function was " << lua_tostring(L, -1) << std::endl;
    lua_pop(L,1);*/


    //lua_close(L);

    //fflush(stdout);

    return app.exec();
}
