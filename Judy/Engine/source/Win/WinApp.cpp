
#include "WinApp.h"
#include <windows.h>

using namespace Judy;

WinApp::WinApp()
{
}

void WinApp::StartMainLoop()
{
    MSG msg;
    while(WindowCount > 0)
    {
        PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
