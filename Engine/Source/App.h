
#pragma once

#include "Object.h"
#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"
#include "Containers/Set.h"
#include "Attributes.h"

class [[Meta]] App : public Object
{
    friend class Meta;

public:
    static App* Instance();

    void StartMainLoop();

    void AddWindow(WindowM* window);
    void RemoveWindow(WindowM* window);

protected:
    App();
    void UpdateCollection();

    Set<WindowM*> Windows;
    Set<WindowM*> AddedWindows;
    Set<WindowM*> RemovedWindows;
};
