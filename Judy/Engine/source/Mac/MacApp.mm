
#include "MacApp.h"

#import <Cocoa/Cocoa.h>

NSApplication* application;

MacApp::MacApp()
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    application = [NSApplication sharedApplication];
}

void MacApp::StartMainLoop()
{
    [application run];
}
