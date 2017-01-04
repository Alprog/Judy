
#pragma once

#include "BaseMenu.h"

class NewMenu : public BaseMenu
{
    Q_OBJECT

public:
    NewMenu(MainWindow* window);

private slots:
    void newSceneFile();
    void newLuaFile();
    void newHlslFile();
};
