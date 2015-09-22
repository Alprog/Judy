
#pragma once

#ifdef WIN
    #include "Win/WinApp.h"
    #include "Win/WinWindow.h"
    #include "Win/WinProcess.h"
    #include "Win/WinSocket.h"
    #include "Win/WinRenderTarget.h"

    using PlatformApp = WinApp;
    using PlatformWindow = WinWindow;
    using PlatformProcess = WinProcess;
    using PlatformSocket = WinSocket;
    using PlatformRenderTarget = WinRenderTarget;
#endif

#if defined(LINUX) || defined(MAC)
    #include "Unix/UnixProcess.h"
    #include "Unix/UnixSocket.h"

    using PlatformProcess = UnixProcess;
    using PlatformSocket = UnixSocket;
#endif

#ifdef LINUX
    #include "Linux/LinuxApp.h"
    #include "Linux/LinuxWindow.h"

    using PlatformApp = LinuxApp;
    using PlatformWindow = LinuxWindow;
#endif

#ifdef MAC
    #include "Mac/MacApp.h"
    #include "Mac/MacWindow.h"

    using PlatformApp = MacApp;
    using PlatformWindow = MacWindow;
#endif


