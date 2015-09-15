
#include "IDE.h"
#include <QFile>
#include <QTextStream>
#include "MainWindow.h"
#include "Meta/Meta.h"

IDE::IDE(int argc, char *argv[])
    : QApplication(argc, argv)
{
    LoadStyle();
    LoadSettings();
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

int IDE::Start()
{
    auto mainWindow = new MainWindow();
    mainWindow->showMaximized();
    windows.push_back(mainWindow);
    return exec();
}
