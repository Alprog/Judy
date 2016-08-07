
#pragma once

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"
#include "Object.h"
#include "Window.h"
#include "Containers/Set.h"
#include "Attributes.h"

class [[Meta]] App : public Object
{
    friend class Meta;

public:
    static App* Instance();

    void StartMainLoop();

    void AddWindow(Window* window);
    void RemoveWindow(Window* window);

protected:
    App();
    void UpdateCollection();

    Set<Window*> Windows;
    Set<Window*> AddedWindows;
    Set<Window*> RemovedWindows;
};
