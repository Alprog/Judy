
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

void WindowM::Render()
{

}

void WindowM::show()
{
}

