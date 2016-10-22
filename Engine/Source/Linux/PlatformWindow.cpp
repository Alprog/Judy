
#include <PlatformWindow.h>
#include <PlatformRenderTarget.h>

#include "App.h"
#include "../Render/RenderManager.h"

#include <stdio.h>
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>

LinuxWindow::LinuxWindow()
{    
    display = XOpenDisplay(NULL);

    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    XWindow root = DefaultRootWindow(display);

    XVisualInfo* vi = glXChooseVisual(display, 0, att);

    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    window = XCreateWindow(display, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, window);
    XStoreName(display, window, "WINDOW");
    XFlush(display);

    renderTarget = new LinuxRenderTarget(display, window);
    renderer = RenderManager::getInstance()->renderers[0];

    App::getInstance()->addWindow(this);
}

void LinuxWindow::processEvents()
{
    XEvent xev;

    while (XCheckWindowEvent(display, window, KeyPressMask, &xev))
    {
    }
}

