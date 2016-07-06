
#pragma once

#include <QApplication>
#include <vector>
#include <string>
#include "Settings.h"
#include "MainWindow.h"
#include "Meta/Serializer.h"
#include "LuaMachine/CallInfo.h"
#include "Render/IRenderer.h"
#include "Node.h"

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
    std::string GetSettingsFilename();

    void Start();
    void LoadStyle();
    void LoadSettings();

signals:
    void SelectScene(Node* scene);
    void SelectNode(Node* node);

private slots:
    void OnPlayerStateChanged();

public:
    Serializer serializer;
    Settings settings;

private:
    std::vector<MainWindow*> windows;
};
