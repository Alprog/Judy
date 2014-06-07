
#pragma once


#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"

    typedef Judy::WinApp PlatformApp;
    typedef Judy::WinWindow PlatformWindow;
#endif

#ifdef LINUX
    #include "Linux/LinuxWindow.h"
    #include "Linux/LinuxApp.h"

    typedef Judy::LinuxApp PlatformApp;
    typedef Judy::LinuxWindow PlatformWindow;
#endif

#ifdef MAC
    #include "Mac/MacWindow.h"
    #include "Mac/MacApp.h"

    typedef Judy::MacApp PlatformApp;
    typedef Judy::MacWindow PlatformWindow;
#endif


