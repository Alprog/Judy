
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"

    typedef WinApp PlatformApp;
    typedef WinWindow PlatformWindow;
#endif

#ifdef LINUX
    #include "Linux/LinuxWindow.h"


#endif
