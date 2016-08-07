
#include "IDE.h"
#include <QFile>
#include <QTextStream>
#include "MainWindow.h"
#include "Meta/Meta.h"
#include "RemotePlayer.h"
#include "Platform.h"

IDE::IDE(int argc, char** argv)
    : QApplication(argc, argv)
{
    Meta::Instance()->Init();

    LoadStyle();
    LoadSettings();
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

std::string IDE::GetSettingsFilename()
{
    return "settings." + GetPlatformName() + ".lua";
}

void IDE::LoadSettings()
{
    Settings::InitMeta();

    auto fileName = GetSettingsFilename();
    QFile file(QString::fromStdString(fileName));
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
    auto fileName = GetSettingsFilename();
    QFile file(QString::fromStdString(fileName));
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
