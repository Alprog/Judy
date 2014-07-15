
#include "Window.h"
#include "Platforms.h"

#include "GLRenderer.h"
#include "DXRenderer.h"

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

auto glRenderer = new GLRenderer();
auto dxRenderer = new DXRenderer();

void Window::Render()
{
    glRenderer->Render(scene, RenderTarget2);
    dxRenderer->Render(scene, RenderTarget1);
}

void Window::show()
{
}

