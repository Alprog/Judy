
#pragma once

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"
#include "SingletonObject.h"
#include "Window.h"
#include "Containers/Set.h"
#include "Attributes.h"

class [[Meta]] App : public SingletonObject<App>
{
    friend class Meta;

public:
    void startMainLoop();

    void addWindow(Window* window);
    void removeWindow(Window* window);

protected:
    void updateCollection();

    Set<Window*> windows;
    Set<Window*> addedWindows;
    Set<Window*> removedWindows;
};
