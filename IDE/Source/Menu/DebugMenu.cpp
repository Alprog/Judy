
#include "DebugMenu.h"
#include "../RemotePlayer.h"

DebugMenu::DebugMenu(MainWindow* window)
    : BaseMenu{"Debug", window}
{
    playAction = createAction("Start", "play", SLOT(play()), Qt::Key_F5);
    pauseAction = createAction("Pause", "pause", SLOT(pause()), Qt::Key_F6);
    stopAction = createAction("Stop", "stop", SLOT(stop()), QKeySequence(Qt::SHIFT +Qt::Key_F6));
    stepActions = {
        createAction("Step Into", "stepinto", SLOT(stepInto()), Qt::Key_F11),
        createAction("Step Over", "stepover", SLOT(stepOver()), Qt::Key_F10),
        createAction("Step Out", "stepout", SLOT(stepOut()), QKeySequence(Qt::SHIFT + Qt::Key_F11))
    };

    addActions({playAction, pauseAction, stopAction});
    addActions(stepActions);

    connect(&timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer.start(100);
}

void DebugMenu::play()
{
    auto player = RemotePlayer::getInstance();
    if (!player->isRunning())
    {
        player->run();
    }
    else if (player->isPaused())
    {
        player->sendCommand("resume");
    }
}

void DebugMenu::stop()
{
    RemotePlayer::getInstance()->stop();
}

void DebugMenu::pause()
{
    RemotePlayer::getInstance()->sendCommand("pause");
}

void DebugMenu::stepInto()
{
    RemotePlayer::getInstance()->sendCommand("stepInto");
}

void DebugMenu::stepOver()
{
    RemotePlayer::getInstance()->sendCommand("stepOver");
}

void DebugMenu::stepOut()
{
    RemotePlayer::getInstance()->sendCommand("stepOut");
}

void DebugMenu::refresh()
{
    RemotePlayer* remotePlayer = RemotePlayer::getInstance();
    bool isRunning = remotePlayer->isRunning();
    bool isConnected = remotePlayer->isConnected();
    bool isPaused = remotePlayer->isPaused();

    playAction->setEnabled(!isRunning || isPaused);
    pauseAction->setEnabled(isConnected && !isPaused);
    stopAction->setEnabled(isRunning);
    for (auto& action : stepActions)
    {
        action->setEnabled(isConnected && isPaused);
    }
}
