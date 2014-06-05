#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QDockWidget* dockWidget;

    static MainWindow* w1;
    static MainWindow* w2;

    void seta(MainWindow* w);

protected:


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
