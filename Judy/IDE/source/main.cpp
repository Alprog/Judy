
#include "App.h"

#include <QApplication>
#include <QWidget>

#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;

    window.resize(600, 600);
    window.setWindowTitle("Judy");
    window.show();

    return app.exec();

}
