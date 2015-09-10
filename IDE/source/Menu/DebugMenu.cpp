
#include "DebugMenu.h"
#include "../RemotePlayer.h"

DebugMenu::DebugMenu()
    : BaseMenu{"Debug"}
{
    playAction = createAction("Start", "play", SLOT(Play()), Qt::Key_F5);
    pauseAction = createAction("Pause", "pause", SLOT(Pause()), Qt::Key_F6);
    stopAction = createAction("Stop", "stop", SLOT(Stop()), QKeySequence(Qt::SHIFT +Qt::Key_F6));
    stepActions = {
        createAction("Step Into", "stepinto", SLOT(StepInto()), Qt::Key_F11),
        createAction("Step Over", "stepover", SLOT(StepOver()), Qt::Key_F10),
        createAction("Step Out", "stepout", SLOT(StepOut()), QKeySequence(Qt::SHIFT + Qt::Key_F11))
    };

    addActions({playAction, pauseAction, stopAction});
    addActions(stepActions);

    connect(&timer, SIGNAL(timeout()), this, SLOT(Refresh()));
    timer.start(100);
}

void DebugMenu::Play()
{
    RemotePlayer::Instance()->Run();
}

void DebugMenu::Pause()
{
}

void DebugMenu::Stop()
{
    RemotePlayer::Instance()->Stop();
}

void DebugMenu::StepInto()
{
}

void DebugMenu::StepOver()
{
}

void DebugMenu::StepOut()
{
}

void DebugMenu::Refresh()
{
    RemotePlayer* remotePlayer = RemotePlayer::Instance();
    bool isRunning = remotePlayer->IsRunning();
    bool isConnected = remotePlayer->IsConnected();

    playAction->setEnabled(!isRunning);
    pauseAction->setEnabled(isConnected);
    stopAction->setEnabled(isRunning);
    for (auto& action : stepActions)
    {
        action->setEnabled(isConnected);
    }
}
