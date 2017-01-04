
#include "NewMenu.h"

NewMenu::NewMenu(MainWindow* window)
    : BaseMenu("New", window)
{
    QList<QAction*> actions
    {
        createAction("Scene", "new_scene", SLOT(newSceneFile())),
        createAction("Lua Script", "new_lua", SLOT(newLuaFile())),
        createAction("HLSL Shader", "new_hlsl", SLOT(newHlslFile()))
    };
    addActions(actions);
}

void NewMenu::newSceneFile()
{
    window->documents->createNewDocument("New Scene.scene");
}

void NewMenu::newLuaFile()
{
    window->documents->createNewDocument("New Script.lua");
}

void NewMenu::newHlslFile()
{
    window->documents->createNewDocument("New Shader.hlsl");
}
