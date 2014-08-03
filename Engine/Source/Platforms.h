
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"
    #include "Win/WinRenderTarget.h"

    using PlatformApp = WinApp;
    using PlatformWindow = WinWindow;
    using PlatformRenderTarget = WinRenderTarget;
#endif

#ifdef LINUX
    #include "Linux/LinuxWindow.h"
    #include "Linux/LinuxApp.h"

    using PlatformApp = LinuxApp;
    using PlatformWindow = LinuxWindow;

#endif

#ifdef MAC
    #include "Mac/MacWindow.h"
    #include "Mac/MacApp.h"

    using PlatformApp = MacApp;
    using PlatformWindow = MacWindow;
#endif


