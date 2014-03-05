#include "mainwindow.h"
#include <QApplication>

#include "qscrollarea.h"
#include <ScintillaEditBase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QScrollArea* area = new QScrollArea(&w);

    Foo* foo = new Foo();
    foo->Bar();

    ScintillaEditBase* s = new ScintillaEditBase(&w);
    s->resize(200, 200);

    w.show();

    return a.exec();
}
