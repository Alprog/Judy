
#pragma once

#include <set>
#include <unordered_set>
#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"

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

    std::set<WindowM*> Windows;
    std::set<WindowM*> AddedWindows;
    std::set<WindowM*> RemovedWindows;
};
