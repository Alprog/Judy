
#include <PlatformInputSystem.h>
#include <cassert>
#include <hidsdi.h>
#include <PlatformInputDevice.h>

#define VK_NUMRETURN 0x0F


auto hkl = LoadKeyboardLayout(L"00000409", 0); // English QWERTY

LRESULT CALLBACK InputWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INPUT:
            {
                //printf("input");

                UINT size;
                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
                auto rawInput = (RAWINPUT*)new char[size];
                GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInput, &size, sizeof(RAWINPUTHEADER));

                if (rawInput->header.dwType == RIM_TYPEKEYBOARD)
                {
                    auto flags = rawInput->data.keyboard.Flags;
                    auto message = rawInput->data.keyboard.Message;
                    auto v = rawInput->data.keyboard.VKey;
                    auto scanCode = rawInput->data.keyboard.MakeCode;
                    auto spec = rawInput->data.keyboard.ExtraInformation;
                    bool e0 = (flags & RI_KEY_E0) == RI_KEY_E0;

                    auto vkey = 0; // Windows virtual key

                    if (scanCode)
                    {
                        if ((flags & RI_KEY_E0) == RI_KEY_E0)
                        {
                            scanCode += 0xe0 << 8;
                        }
                        else if((flags & RI_KEY_E1) == RI_KEY_E1)
                        {
                            scanCode += 0xe1 << 8;
                        }
                        vkey = MapVirtualKeyEx(scanCode, MAPVK_VSC_TO_VK_EX, hkl);
                        printf("try convert %i %i %i\n", rawInput->data.keyboard.MakeCode, flags, vkey);
                    }

                    if (vkey == 0)
                    {
                        vkey = rawInput->data.keyboard.VKey;
                    }

                    printf("+++%i %i\n", vkey, v);

                    switch (vkey)
                    {
                        case VK_INSERT:
                            if (!e0) vkey = VK_NUMPAD0;
                            break;

                        case VK_END:
                            if (!e0) vkey = VK_NUMPAD1;
                            break;

                        case VK_DOWN:
                            if (!e0) vkey = VK_NUMPAD2;
                            break;

                        case VK_NEXT: // PgUp
                            if (!e0) vkey = VK_NUMPAD3;
                            break;

                        case VK_LEFT:
                            if (!e0) vkey = VK_NUMPAD4;
                            break;

                        case VK_CLEAR:
                            if (!e0) vkey = VK_NUMPAD5;
                            break;

                        case VK_RIGHT:
                            if (!e0) vkey = VK_NUMPAD6;
                            break;

                        case VK_HOME:
                            if (!e0) vkey = VK_NUMPAD7;
                            break;

                        case VK_UP:
                            if (!e0) vkey = VK_NUMPAD8;
                            break;

                        case VK_PRIOR: // PgDn
                            if (!e0) vkey = VK_NUMPAD9;
                            break;

                        case VK_DELETE:
                            if (!e0) vkey = VK_DECIMAL;
                            break;

                        case VK_RETURN:
                            if (e0) vkey = VK_NUMRETURN;
                            break;

                        case VK_OEM_2: // slash
                            if (e0) vkey = VK_DIVIDE;
                            break;
                    }

                    printf("--- %i %i\n", vkey, v);
                    break;

                }

                if (rawInput->header.dwType == RIM_TYPEMOUSE)
                {
                    auto x = rawInput->data.mouse.lLastX;
                    auto y = rawInput->data.mouse.lLastY;
                    auto flags = rawInput->data.mouse.usFlags;

                    auto b = rawInput->data.mouse.ulRawButtons;
                    //printf("%i\n", b);

                    //printf("%i %i %i\n", x, y, flags);
                }

                delete[] rawInput;
            }
            break;


        case WM_INPUT_DEVICE_CHANGE:
            printf("input device change");
            break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void WinInputSystem::findDevices()
{
    RAWINPUTDEVICELIST* pRawInputDeviceList;

    UINT deviceCount;
    auto err = GetRawInputDeviceList(nullptr, &deviceCount, sizeof(RAWINPUTDEVICELIST));
    assert(!err);

    auto deviceHeaders = new RAWINPUTDEVICELIST[deviceCount];
    err = GetRawInputDeviceList(deviceHeaders, &deviceCount, sizeof(RAWINPUTDEVICELIST));

    for (int i = 0; i < deviceCount; i++)
    {
        auto& deviceHeader = deviceHeaders[i];

        RID_DEVICE_INFO info = {};
        UINT size = sizeof(RID_DEVICE_INFO);
        auto result = GetRawInputDeviceInfo(deviceHeader.hDevice, RIDI_DEVICEINFO, &info, &size);

        auto type = InputDeviceType::Unknown;

        switch (info.dwType)
        {
            case RIM_TYPEMOUSE:
                printf("Mouse: %i\n", info.mouse.dwNumberOfButtons);
                type = InputDeviceType::Mouse;
                break;

            case RIM_TYPEKEYBOARD:


                printf("Keyboard: %i %i\n", info.keyboard.dwNumberOfKeysTotal, info.keyboard.dwKeyboardMode);
                type = InputDeviceType::Keyboard;
                break;

            case RIM_TYPEHID:
                if (info.hid.usUsagePage == 1 && info.hid.usUsage == 5)
                {
                    printf("GamePad: %i %i\n");
                    type = InputDeviceType::GamePad;
                }
                break;
        }

        if (type == InputDeviceType::Unknown)
            continue;

        GetRawInputDeviceInfo(deviceHeader.hDevice, RIDI_PREPARSEDDATA, nullptr, &size);
        void* preparsedData = new char[size];
        GetRawInputDeviceInfo(deviceHeader.hDevice, RIDI_PREPARSEDDATA, preparsedData, &size);

        auto device = new WinInputDevice();
        device->type = type;
        //device- = preparsedData;
        devices.push_back(device);
    }

    delete[] deviceHeaders;
}

WinInputSystem::WinInputSystem()
{
    initKeys();
    findDevices();

    auto hInstance = GetModuleHandle(nullptr);
    LPCWSTR className = L"InputWindow";

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = InputWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(0, className, 0, 0, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

    RAWINPUTDEVICE Rid[3];

    Rid[0].usUsagePage = 0x01;
    Rid[0].usUsage = 0x06;
    Rid[0].dwFlags = RIDEV_INPUTSINK;
    Rid[0].hwndTarget = hWnd;

    Rid[1].usUsagePage = 0x01;
    Rid[1].usUsage = 0x02;
    Rid[1].dwFlags = RIDEV_INPUTSINK;
    Rid[1].hwndTarget = hWnd;

    Rid[2].usUsagePage = 0x01;
    Rid[2].usUsage = 0x05;
    Rid[2].dwFlags = RIDEV_INPUTSINK;
    Rid[2].hwndTarget = hWnd;

    bool result = RegisterRawInputDevices(Rid, 3, sizeof(RAWINPUTDEVICE));
    result = true;
}

void WinInputSystem::initKeys()
{
    keys.resize(256, Key::Unknown);

    keys[VK_SHIFT] = Key::Ambiguity;
    keys[VK_CONTROL] = Key::Ambiguity;
    keys[VK_MENU] = Key::Ambiguity;

    keys[VK_LBUTTON] = Key::Mouse_LMB;
    keys[VK_RBUTTON] = Key::Mouse_RMB;
    keys[VK_MBUTTON] = Key::Mouse_MMB;
    keys[VK_XBUTTON1] = Key::Mouse_X1;
    keys[VK_XBUTTON2] = Key::Mouse_X2;
    keys[VK_BACK] = Key::Key_Backspace;
    keys[VK_TAB] = Key::Key_Tab;
    keys[VK_RETURN] = Key::Key_Enter;

    keys[VK_PAUSE] = Key::Key_PauseBreak;
    keys[VK_CAPITAL] = Key::Key_CapsLock;
    keys[VK_ESCAPE] = Key::Key_Escape;

    keys[VK_SPACE] = Key::Key_Space;
    keys[VK_PRIOR] = Key::Key_PageUp;
    keys[VK_NEXT] = Key::Key_PageDown;
    keys[VK_END] = Key::Key_End;
    keys[VK_HOME] = Key::Key_Home;
    keys[VK_LEFT] = Key::Key_Left;
    keys[VK_UP] = Key::Key_Up;
    keys[VK_RIGHT] = Key::Key_Right;
    keys[VK_DOWN] = Key::Key_Down;

    keys[VK_SNAPSHOT] = Key::Key_PrintScreen;
    keys[VK_INSERT] = Key::Key_Insert;
    keys[VK_DELETE] = Key::Key_Delete;
    keys['0'] = Key::Key_0;
    keys['1'] = Key::Key_1;
    keys['2'] = Key::Key_2;
    keys['3'] = Key::Key_3;
    keys['4'] = Key::Key_4;
    keys['5'] = Key::Key_5;
    keys['6'] = Key::Key_6;
    keys['7'] = Key::Key_7;
    keys['8'] = Key::Key_8;
    keys['9'] = Key::Key_9;
    keys['A'] = Key::Key_A;
    keys['B'] = Key::Key_B;
    keys['C'] = Key::Key_C;
    keys['D'] = Key::Key_D;
    keys['E'] = Key::Key_E;
    keys['F'] = Key::Key_F;
    keys['G'] = Key::Key_G;
    keys['H'] = Key::Key_H;
    keys['I'] = Key::Key_I;
    keys['J'] = Key::Key_J;
    keys['K'] = Key::Key_K;
    keys['L'] = Key::Key_L;
    keys['M'] = Key::Key_M;
    keys['N'] = Key::Key_N;
    keys['O'] = Key::Key_O;
    keys['P'] = Key::Key_P;
    keys['Q'] = Key::Key_Q;
    keys['R'] = Key::Key_R;
    keys['S'] = Key::Key_S;
    keys['T'] = Key::Key_T;
    keys['U'] = Key::Key_U;
    keys['V'] = Key::Key_V;
    keys['W'] = Key::Key_W;
    keys['X'] = Key::Key_X;
    keys['Y'] = Key::Key_Y;
    keys['Z'] = Key::Key_Z;
    keys[VK_LWIN] = Key::Key_L_Windows;
    keys[VK_RWIN] = Key::Key_R_Windows;
    keys[VK_APPS] = Key::Key_Application;

    keys[VK_NUMPAD0] = Key::Key_Num0;
    keys[VK_NUMPAD1] = Key::Key_Num1;
    keys[VK_NUMPAD2] = Key::Key_Num2;
    keys[VK_NUMPAD3] = Key::Key_Num3;
    keys[VK_NUMPAD4] = Key::Key_Num4;
    keys[VK_NUMPAD5] = Key::Key_Num5;
    keys[VK_NUMPAD6] = Key::Key_Num6;
    keys[VK_NUMPAD7] = Key::Key_Num7;
    keys[VK_NUMPAD8] = Key::Key_Num8;
    keys[VK_NUMPAD9] = Key::Key_Num9;
    keys[VK_MULTIPLY] = Key::Key_NumMultiply;
    keys[VK_ADD] = Key::Key_NumPlus;
    keys[VK_DECIMAL] = Key::Key_NumDecimal;
    keys[VK_SUBTRACT] = Key::Key_NumMinus;
    keys[VK_DIVIDE] = Key::Key_NumDivide;
    keys[VK_NUMRETURN] = Key::Key_NumEnter;
    keys[VK_F1] = Key::Key_F1;
    keys[VK_F2] = Key::Key_F2;
    keys[VK_F3] = Key::Key_F3;
    keys[VK_F4] = Key::Key_F4;
    keys[VK_F5] = Key::Key_F5;
    keys[VK_F6] = Key::Key_F6;
    keys[VK_F7] = Key::Key_F7;
    keys[VK_F8] = Key::Key_F8;
    keys[VK_F9] = Key::Key_F9;
    keys[VK_F10] = Key::Key_F10;
    keys[VK_F11] = Key::Key_F11;
    keys[VK_F12] = Key::Key_F12;

    keys[VK_NUMLOCK] = Key::Key_NumLock;
    keys[VK_SCROLL] = Key::Key_ScrollLock;
    keys[VK_LSHIFT] = Key::Key_L_Shift;
    keys[VK_RSHIFT] = Key::Key_R_Shift;
    keys[VK_LCONTROL] = Key::Key_L_Control;
    keys[VK_RCONTROL] = Key::Key_R_Control;
    keys[VK_LMENU] = Key::Key_L_Alt;
    keys[VK_RMENU] = Key::Key_R_Alt;
    keys[VK_OEM_PLUS] = Key::Key_Plus;
    keys[VK_OEM_COMMA] = Key::Key_Comma;
    keys[VK_OEM_MINUS] = Key::Key_Minus;
    keys[VK_OEM_PERIOD] = Key::Key_Period;

    keys[VK_OEM_1] = Key::Key_Semicolon;
    keys[VK_OEM_2] = Key::Key_Slash;
    keys[VK_OEM_3] = Key::Key_Tilde;
    keys[VK_OEM_4] = Key::Key_L_Bracket;
    keys[VK_OEM_5] = Key::Key_Backslash;
    keys[VK_OEM_6] = Key::Key_R_Bracket;
    keys[VK_OEM_7] = Key::Key_Quote;
}

WinInputSystem::~WinInputSystem()
{
}

void WinInputSystem::updateState()
{
    MSG msg;
    PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);

//    for (auto& device : devices)
//    {
//        if (device.Type != InputDeviceType::GamePad)
//            continue;

//        auto data = (PHIDP_PREPARSED_DATA)device.Data;

//        HIDP_CAPS Caps;
//        HidP_GetCaps(data, &Caps);

//        auto buttonCaps = new HIDP_BUTTON_CAPS[Caps.NumberInputButtonCaps];
//        HidP_GetButtonCaps(HidP_Input, buttonCaps, &Caps.NumberInputButtonCaps, data);


//        for (int i = 0; i < Caps.NumberInputButtonCaps; i++)
//        {
//            auto& caps = buttonCaps[i];
//            ULONG count = caps.Range.UsageMax - caps.Range.UsageMin + 1;
//            printf("%i [%i-%i]", count, caps.Range.UsageMin, caps.Range.UsageMax);

//            auto usages = new USAGE[count];
//            PCHAR report = new char[1000];
//            HidP_GetUsages(HidP_Input, caps.UsagePage, 0, usages, &count, data, report, 1000);

//            for (int j = 0; j < count; j++)
//            {
//                USAGE usage = usages[j];
//                if (usage)
//                {
//                    printf("BUTTON %i", usage);
//                }

//            }

//        }

//    }

}

