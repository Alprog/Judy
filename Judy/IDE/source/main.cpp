
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

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();

    QString sheet =
        "QWidget {"
        "color: #C0C0C0;"
        "background-color: #2D2D2D;"
        "}"
        "QMenuBar::item  {"
        "background: #2D2D2D;"
        "}"
        "QMenuBar::item:selected  {"
        "background: #333333;"
        "}"
        "QMenu::item  {"
        "background: #1B1B1B;"
        "}"
        "QMenu::item:selected  {"
        "background: #333333;"
        "}"
        "QToolBar  {"
        "border: none;"
        "}"
        ;

    app.setStyleSheet(sheet);

    return app.exec();
}


int maina(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(600, 600);
    window.setWindowTitle("Judy IDE");
    window.showMaximized();

    QDockWidget dockWidget("name", 0, 0);
    dockWidget.setWidget(new QTextEdit);
    window.addDockWidget(Qt::LeftDockWidgetArea, &dockWidget);

    QDockWidget dockWidget2("name2", 0, 0);;
    dockWidget2.setWidget(new QTextEdit);
    window.addDockWidget(Qt::RightDockWidgetArea, &dockWidget2);


    ScintillaEdit edit;
    window.setCentralWidget(&edit);



    //QDockWidget dockWidget2;
    //dockWidget2.setWidget(&edit);
    //window.addDockWidget(Qt::RightDockWidgetArea, &dockWidget2);

    int a = window.winId();

    printf("%i", a);
    fflush(stdout);

    return app.exec();

}
