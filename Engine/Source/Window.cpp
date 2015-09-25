
#include "Window.h"
#include "Platforms.h"

#ifdef WIN
#include "GLRenderer.h"
#include "DXRenderer.h"
#endif

#include "Quad.h"

WindowM* WindowM::Create()
{
    return new PlatformWindow();
}

WindowM::WindowM()
{

}

#ifdef WIN

auto glRenderer = new GLRenderer();
auto dxRenderer = new DXRenderer();

void WindowM::Render()
{
//    auto quad = (Quad*)scene;
//    quad->Transform.Rotation += 0.04f;
//    glRenderer->Render(scene, RenderTarget2);
//    dxRenderer->Render(scene, RenderTarget1);
}
#else

void WindowM::Render()
{
}


#endif

void WindowM::show()
{
}

