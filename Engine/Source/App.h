
#pragma once

#include "Scriptable.h"
#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"
#include "Containers/Set.h"
#include "Attributes.h"

class _(Meta)__ App : public Scriptable
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
