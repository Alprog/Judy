
#include "Window.h"
#include "Platforms.h"

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

void Window::show()
{
}

