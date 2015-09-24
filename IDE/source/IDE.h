
#pragma once

#include <QApplication>
#include <vector>
#include "Settings.h"
#include "MainWindow.h"
#include "Meta/Serializer.h"
#include "LuaMachine/CallInfo.h"

class IDE : public QApplication
{
    Q_OBJECT

    friend int main(int argc, char *argv[]);

    IDE(int argc, char** argv);

public:
    static IDE* Instance();
    void SaveSettings();
    MainWindow* GetMainWindow();
    void FollowToCall(CallInfo callInfo);

private:
    void Start();
    void LoadStyle();
    void LoadSettings();

private slots:
    void OnPlayerStateChanged();

public:
    Serializer serializer;
    Settings settings;

private:
    std::vector<MainWindow*> windows;
};
