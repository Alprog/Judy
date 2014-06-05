#include "mainwindow.h"
#include <QApplication>

#include <QDockWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow::w1 = new MainWindow();


    MainWindow::w2 = new MainWindow();



    MainWindow::w1->seta(MainWindow::w1);
    MainWindow::w2->seta(MainWindow::w2);

    MainWindow::w1->show();
    MainWindow::w2->show();

    return a.exec();
}
