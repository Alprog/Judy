
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"
    #include "Win/WinRenderTarget.h"
    #include "Win/WinSocket.h"

    using PlatformApp = WinApp;
    using PlatformWindow = WinWindow;
    using PlatformRenderTarget = WinRenderTarget;
    using PlatformSocket = WinSocket;
#endif

#ifdef LINUX
    #include "Linux/LinuxWindow.h"
    #include "Linux/LinuxApp.h"

    using PlatformApp = LinuxApp;
    using PlatformWindow = LinuxWindow;
    using PlatformSocket = UnixSocket;
#endif

#ifdef MAC
    #include "Mac/MacWindow.h"
    #include "Mac/MacApp.h"
    #include "Unix/UnixSocket.h"

    using PlatformApp = MacApp;
    using PlatformWindow = MacWindow;
    using PlatformSocket = UnixSocket;
#endif


