
#include "LinuxWindow.h"

#include "App.h"
#include "../Render/RenderManager.h"
#include "LinuxRenderTarget.h"

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
    renderer = RenderManager::Instance()->renderers[0];

    App::Instance()->AddWindow(this);

    /*GLXContext glc = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, win, glc);

    XEvent xev;
    float a = 0;
    while(1)
    {
        a = 1 - a;
        glClearColor( 1.0, a, 0.0, 1.0 );
        glClear(GL_COLOR_BUFFER_BIT );
        glXSwapBuffers(display, win);

        if(XCheckWindowEvent(display, win, KeyPressMask, &xev))
        {
            printf("HEREd \n");
            fflush(stdout);
        }


        if(XCheckWindowEvent(display, win, StructureNotifyMask, &xev))
        {
            printf("HEREd %i \n", xev.xconfigure.x);
            fflush(stdout);
        }


    }*/

    /*XWindowAttributes gwa;

    //XGetWindowAttributes(display, win, &gwa);
    //glViewport(0, 0, gwa.width, gwa.height);
    //DrawAQuad();
    //glXSwapBuffers(display, win);

    XEvent xev;

    while (1) {
          XNextEvent(display, &xev);
          if (xev.type == Expose) {
             //XFillRectangle(display, win, DefaultGC(display, 0), 20, 20, 10, 10);
          }
          if (xev.type == KeyPress)
             break;

       }

    while(1)
    {
        XNextEvent(display, &xev);
        if(xev.type == Expose)
        {


        }
        else if(xev.type == KeyPress)
        {
            glXMakeCurrent(display, None, NULL);
            glXDestroyContext(display, glc);
            XDestroyWindow(display, win);
            XCloseDisplay(display);
            break;
        }
    }

    printf("HEREd %i \n", a);
    fflush(stdout);
    */
}

void LinuxWindow::ProcessEvents()
{
    XEvent xev;
    if (XCheckWindowEvent(display, window, KeyPressMask, &xev))
    {
        printf("HEREd \n");
        fflush(stdout);
    }
}

