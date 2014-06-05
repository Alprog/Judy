#include "mainwindow.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QApplication>
#include <QtTest/QTestEventList>

static QDockWidget* dww = NULL;
MainWindow* MainWindow::w1 = NULL;
MainWindow* MainWindow::w2 = NULL;

QDockWidget* dock1;
QDockWidget* dock2;
QDockWidget* dock3;

class QDockWidgetA : QDockWidget
{
public:
    QDockWidgetA(QString s)
        : QDockWidget(s)
    {
        cloneW = NULL;
        dragMode = false;
        a = false;
    }

    QDockWidgetA* cloneW;
    bool dragMode;
    QPoint mpos;
    bool a;

    bool QDockWidgetA::event ( QEvent* e )
    {
        if (e->type() == QEvent::Move)
        {
            int x = this->parentWidget()->pos().x();

            printf("%i\n", x);
            fflush(stdout);
        }

        if (e->type() == QEvent::KeyPress)
        {


            if (this->parent() == MainWindow::w1)
            {
                printf("SAME");
                fflush(stdout);
            }
            else
            {
                MainWindow::w1->restoreDockWidget(this);
                setFloating(true);


                printf("CHANGE");
                fflush(stdout);
            }

        }

        /*if (e->type() == QEvent::NonClientAreaMouseButtonPress)
        {
            printf("a");
            fflush(stdout);
            return false;
        }*/

        /*if (e->type() == QEvent::MouseButtonPress)
        {
            printf("m");
            fflush(stdout);
        }*/

        /*if (e->type() == QEvent::Move)
        {
            QMoveEvent* me = (QMoveEvent*)e;
            //printf("fef", )
            int x = me->pos().x();
            if (!a && x > 1200)
            {
                a = true;
                printf("!");
                fflush(stdout);

                QTestEventList *eventos = new QTestEventList();
                eventos->addMouseRelease(Qt::LeftButton, 0, QPoint(100, 10), -1);
                eventos->simulate(this);

                //close();
                MainWindow::w1->addDockWidget(Qt::LeftDockWidgetArea, this);
                this->setFloating(true);
                //show();

                eventos = new QTestEventList();
                eventos->addMousePress(Qt::LeftButton, 0, QPoint(100, 10), -1);
                eventos->simulate(this);

                dragMode = true;
            }
        }

        if (e->type() == QEvent::MouseMove)
        {
            if (dragMode)
            {
                QMouseEvent* me = (QMouseEvent*)e;
                QPoint diff = me->pos() - mpos;
                QPoint newpos = this->pos() + diff;
                this->move(newpos);
            }
        }*/

        /*if (e->type() == QEvent::MouseButtonPress)
        {
           if (isFloating())
           {
               dragMode = true;

               QMouseEvent* me = (QMouseEvent*)e;
               mpos = me->pos();
           }
        }

        if (e->type() == QEvent::MouseButtonRelease)
        {
            dragMode = false;
        }

        */

        return QDockWidget::event(e);
    }
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->resize(600, 600);

    this->setDockOptions(dockOptions() | QMainWindow::AllowNestedDocks);

    dock1 = (QDockWidget*)(new QDockWidgetA("1"));
    dock2 = (QDockWidget*)(new QDockWidgetA("2"));
    dock3 = (QDockWidget*)(new QDockWidgetA("3"));
}

void MainWindow::seta(MainWindow* w)
{
    addDockWidget(Qt::LeftDockWidgetArea, dock1);
    addDockWidget(Qt::LeftDockWidgetArea, dock2);
    addDockWidget(Qt::LeftDockWidgetArea, dock3);
}

MainWindow::~MainWindow()
{

}

