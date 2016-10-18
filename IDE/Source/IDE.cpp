
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
    Meta::instance()->init();

    loadStyle();
    loadSettings();
    start();
}

IDE* IDE::instance()
{
    return static_cast<IDE*>(QApplication::instance());
}

void IDE::loadStyle()
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

std::string IDE::getSettingsFilename()
{
    return "settings." + getPlatformName() + ".lua";
}

void IDE::loadSettings()
{
    Settings::initMeta();

    auto fileName = getSettingsFilename();
    QFile file(QString::fromStdString(fileName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        auto text = stream.readAll().toStdString();
        settings = serializer.deserialize(text);
        file.close();
    }
}

void IDE::saveSettings()
{
    auto fileName = getSettingsFilename();
    QFile file(QString::fromStdString(fileName));
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    auto text = serializer.serialize(settings);
    stream << tr(text.c_str());
    file.close();
}

void IDE::start()
{
    auto mainWindow = new MainWindow();
    mainWindow->showMaximized();
    windows.push_back(mainWindow);
}

MainWindow* IDE::getMainWindow()
{
    return windows[0];
}

void IDE::followToCall(CallInfo callInfo)
{
    auto mainWindow = windows[0];
    auto path = Path::combine(settings.projectPath, callInfo.source.substr(1));
    mainWindow->documents->openAtLine(path, callInfo.line);
}

void IDE::onPlayerStateChanged()
{
    auto& calls = RemotePlayer::instance()->stack.calls;
    if (calls.size() > 0)
    {
        followToCall(calls[0]);
    }
}
