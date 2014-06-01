
#include "MacWindow.h"
#include "App.h"

#import <Cocoa/Cocoa.h>

MacWindow::MacWindow()
{
    NSWindow* window = [NSWindow alloc];

    NSRect rect = NSMakeRect(200, 200, 600, 600);

    int mask = NSTitledWindowMask | NSClosableWindowMask;
    mask = mask | NSMiniaturizableWindowMask | NSResizableWindowMask;

    int backing = NSBackingStoreBuffered;

    [window initWithContentRect:rect styleMask:mask backing:backing defer:NO];

    [window makeKeyAndOrderFront:window];

}

void MacWindow::SetContext()
{
}

void MacWindow::Swap()
{
}
