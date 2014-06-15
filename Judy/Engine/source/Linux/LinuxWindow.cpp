
#include "LinuxWindow.h"

#define Window XWindow
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#undef Window

#include <stdio.h>

void DrawAQuad() {
 glClearColor(1.0, 0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1., 1., -1., 1., 1., 20.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
  glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
  glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
  glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
 glEnd();
}


LinuxWindow::LinuxWindow()
{    
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    Display *display = XOpenDisplay(NULL);
    XWindow root = DefaultRootWindow(display);

    XVisualInfo* vi = glXChooseVisual(display, 0, att);

    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    XWindow win = XCreateWindow(display, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, win);
    XStoreName(display, win, "WINDOW");
    XFlush(display);

    GLXContext glc = glXCreateContext(display, vi, NULL, GL_TRUE);
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


    }

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

}

void LinuxWindow::SetContext()
{
}

void LinuxWindow::Swap()
{
}

