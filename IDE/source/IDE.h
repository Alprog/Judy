
#pragma once

#include <QApplication>
#include <vector>
#include "Settings.h"
#include "MainWindow.h"
#include "Meta/Serializer.h"

class IDE : public QApplication
{
    friend int main(int argc, char *argv[]);

    IDE(int argc, char *argv[]);

public:
    static IDE* Instance();
    int Start();
    void SaveSettings();
    MainWindow* GetMainWindow();

private:
    void LoadStyle();
    void LoadSettings();

public:
    Serializer serializer;
    Settings settings;

private:
    std::vector<MainWindow*> windows;
};
