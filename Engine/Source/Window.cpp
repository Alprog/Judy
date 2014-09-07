
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
    auto quad = new Quad();
    quad->Size = {0.8, 0.8};
    quad->Shader = L"Shaders\\Color";
    quad->Texture = L"D:/test.png";

    auto child = new Quad();
    child->Size = {0.5, 0.5};
    child->Shader = L"Shaders\\Color";
    child->Texture = L"D:/test.png";

    quad->AddChild(child);

    scene = quad;
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

