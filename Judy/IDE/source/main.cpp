
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
