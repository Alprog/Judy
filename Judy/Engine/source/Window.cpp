
#include "Window.h"
#include "Platforms.h"

JWindow* JWindow::Create()
{
    return (JWindow*)new PlatformWindow();
}

void JWindow::show()
{
}

