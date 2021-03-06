
#include "MacWindow.h"
#include "App.h"

#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>

NSOpenGLView* view;

MacWindow::MacWindow()
{
    NSOpenGLContext* gl;
    
    NSWindow* window = [NSWindow alloc];

    NSRect rect = NSMakeRect(200, 200, 600, 600);

    int mask = NSTitledWindowMask | NSClosableWindowMask;
    mask = mask | NSMiniaturizableWindowMask | NSResizableWindowMask;

    auto backing = NSBackingStoreBuffered;

    [window initWithContentRect:rect styleMask:mask backing:backing defer:NO];

    NSOpenGLPixelFormatAttribute attributes[] =
    {
        NSOpenGLPFADoubleBuffer,
        0
    };
    NSOpenGLPixelFormat* format = [NSOpenGLPixelFormat alloc];
    [format initWithAttributes:attributes];

    view = [NSOpenGLView alloc];
    [view initWithFrame:rect pixelFormat:format];

    [window setContentView: view];
    [window makeKeyAndOrderFront:window];
}

void MacWindow::processEvents()
{

}

void MacWindow::setContext()
{
    [[view openGLContext] makeCurrentContext];
}

void MacWindow::swap()
{
    [[view openGLContext] flushBuffer];
}
