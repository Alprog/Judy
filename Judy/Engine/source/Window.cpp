
#include "Window.h"
#include "Platforms.h"

using namespace Judy;

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

void Window::show()
{
}

