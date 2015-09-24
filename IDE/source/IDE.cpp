
#include "IDE.h"
#include <QFile>
#include <QTextStream>
#include "MainWindow.h"
#include "Meta/Meta.h"
#include "RemotePlayer.h"

IDE::IDE(int argc, char** argv)
    : QApplication(argc, argv)
{
    LoadStyle();
    LoadSettings();

    //connect(RemotePlayer::Instance(), SIGNAL(StateChanged()), this, SLOT(OnPlayerStateChanged()));

    Start();
}

IDE* IDE::Instance()
{
    return static_cast<IDE*>(QApplication::instance());
}

void IDE::LoadStyle()
{
    QFile file("style.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString sheet = stream.readAll();
        setStyleSheet(sheet);
    }
    file.close();
}

void IDE::LoadSettings()
{
    Settings::InitMeta();

    QFile file("settings.lua");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        auto text = stream.readAll().toStdString();
        settings = serializer.Deserialize(text);
        file.close();
    }
}

void IDE::SaveSettings()
{
    QFile file(tr("settings.lua"));
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    auto text = serializer.Serialize(settings);
    stream << tr(text.c_str());
    file.close();
}

void IDE::Start()
{
    auto mainWindow = new MainWindow();
    mainWindow->showMaximized();
    windows.push_back(mainWindow);
}

MainWindow* IDE::GetMainWindow()
{
    return windows[0];
}

void IDE::FollowToCall(CallInfo callInfo)
{
    auto mainWindow = windows[0];
    auto path = Path::Combine(settings.projectPath, callInfo.source.substr(1));
    mainWindow->documents->OpenAtLine(path, callInfo.line);
}

void IDE::OnPlayerStateChanged()
{
    auto& calls = RemotePlayer::Instance()->stack.calls;
    if (calls.size() > 0)
    {
        FollowToCall(calls[0]);
    }
}
