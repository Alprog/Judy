
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
    static App* instance();

    void startMainLoop();

    void addWindow(Window* window);
    void removeWindow(Window* window);

protected:
    App();
    void updateCollection();

    Set<Window*> windows;
    Set<Window*> addedWindows;
    Set<Window*> removedWindows;
};
