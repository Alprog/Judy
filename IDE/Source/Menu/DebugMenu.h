
#pragma once

#include "BaseMenu.h"
#include <QTimer>

class DebugMenu : public BaseMenu
{
    Q_OBJECT

public:
    DebugMenu(MainWindow* window);

    QAction* playAction;
    QAction* pauseAction;
    QAction* stopAction;
    QList<QAction*> stepActions;

private slots:
    void play();
    void pause();
    void stop();
    void stepInto();
    void stepOver();
    void stepOut();

    void refresh();

private:
    QTimer timer;
};
