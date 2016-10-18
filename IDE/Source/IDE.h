
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
    static IDE* instance();
    void saveSettings();
    MainWindow* getMainWindow();
    void followToCall(CallInfo callInfo);

private:
    std::string getSettingsFilename();

    void start();
    void loadStyle();
    void loadSettings();

signals:
    void selectScene(Node* scene);
    void selectNode(Node* node);

private slots:
    void onPlayerStateChanged();

public:
    Serializer serializer;
    Settings settings;

private:
    std::vector<MainWindow*> windows;
};
