
#include "Window.h"
#include "Platforms.h"

#include "GLRenderer.h"
#include "DXRenderer.h"

#include "Quad.h"

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

Window::Window()
{
}

auto glRenderer = new GLRenderer();
auto dxRenderer = new DXRenderer();

void Window::Render()
{
    auto quad = (Quad*)scene;
    quad->Transform.Rotation += 0.04f;
    glRenderer->Render(scene, RenderTarget2);
    dxRenderer->Render(scene, RenderTarget1);
}

void Window::show()
{
}

