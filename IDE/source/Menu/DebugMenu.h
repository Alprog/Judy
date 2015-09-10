
#pragma once

#include "BaseMenu.h"
#include <QTimer>

class DebugMenu : public BaseMenu
{
    Q_OBJECT

public:
    DebugMenu();

    QAction* playAction;
    QAction* pauseAction;
    QAction* stopAction;
    std::vector<QAction*> stepActions;

private slots:
    void Play();
    void Pause();
    void Stop();
    void StepInto();
    void StepOver();
    void StepOut();

    void Refresh();

private:
    QTimer timer;
};
