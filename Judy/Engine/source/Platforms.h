
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"

    typedef WinApp PlatformApp;
    typedef WinWindow PlatformWindow;
#endif

#ifdef LINUX
    #include "Linux/LinuxWindow.h"
    #include "Linux/LinuxApp.h"

    typedef LinuxApp PlatformApp;
    typedef LinuxWindow PlatformWindow;
#endif

#ifdef MAC
    #include "Mac/MacWindow.h"
    #include "Mac/MacApp.h"

    typedef MacApp PlatformApp;
    typedef MacWindow PlatformWindow;
#endif
