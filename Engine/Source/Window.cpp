
#include "Window.h"
#include "Platforms.h"

#ifdef WIN
#include "GLRenderer.h"
#include "DXRenderer.h"
#endif

#include "Quad.h"

Window* Window::Create()
{
    return (Window*)new PlatformWindow();
}

Window::Window()
{
}

#ifdef WIN

auto glRenderer = new GLRenderer();
auto dxRenderer = new DXRenderer();

void Window::Render()
{
    auto quad = (Quad*)scene;
    quad->Transform.Rotation += 0.04f;
    glRenderer->Render(scene, RenderTarget2);
    dxRenderer->Render(scene, RenderTarget1);
}
#else

void Window::Render()
{
}


#endif

void Window::show()
{
}

