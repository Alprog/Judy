
#include "App.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "MainWindow.h"
#include "Meta/Meta.h"

int main(int argc, char *argv[])
{
    Meta::Instance();

    QApplication app(argc, argv);

    QFile file("style.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString sheet = stream.readAll();
        app.setStyleSheet(sheet);
    }
    file.close();

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}

