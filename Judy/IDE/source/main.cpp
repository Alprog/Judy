
#include "../../../3rd-Party/scintilla/qt/ScintillaEditBase.h"
#include "../../../3rd-Party/scintilla/qt/ScintillaEdit.h"

#define Window W
#include "App.h"
#define Window Window

#include <QApplication>
#include <QWidget>

#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(600, 600);
    window.setWindowTitle("Judy");

    ScintillaEdit edit(&window);
    edit.resize(600, 600);

    //window.showMaximized();
    window.show();


    int a = window.winId();

    printf("%i", a);
    fflush(stdout);

    return app.exec();

}
