
#pragma once

#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"
#include "Containers/Set.h"

#define __Meta__

class __Meta__ App
{
    friend class Meta;

public:
    static App* Instance();

    void StartMainLoop();

    void AddWindow(WindowM* window);
    void RemoveWindow(WindowM* window);

private:
    void UpdateCollection();

    Set<WindowM*> Windows;
    Set<WindowM*> AddedWindows;
    Set<WindowM*> RemovedWindows;
};
