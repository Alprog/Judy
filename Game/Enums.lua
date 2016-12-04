
function Enum(table)
    local enum = {}
    for i, value in ipairs(table) do
        enum[value] = i
    end
    return enum
end

RendererType = Enum
({
    [0] = "DX",
    "GL",
    "Vulkan",
    
    "COUNT"
})

Keys = Enum
({
    [0] = "Unknown",
    "Ambiguity",

    "Mouse_LMB",
    "Mouse_RMB",
    "Mouse_MMB",
    "Mouse_X1",
    "Mouse_X2",

    "Key_Escape",

    "Key_F1",
    "Key_F2",
    "Key_F3",
    "Key_F4",
    "Key_F5",
    "Key_F6",
    "Key_F7",
    "Key_F8",
    "Key_F9",
    "Key_F10",
    "Key_F11",
    "Key_F12",

    "Key_0",
    "Key_1",
    "Key_2",
    "Key_3",
    "Key_4",
    "Key_5",
    "Key_6",
    "Key_7",
    "Key_8",
    "Key_9",

    "Key_A",
    "Key_B",
    "Key_C",
    "Key_D",
    "Key_E",
    "Key_F",
    "Key_G",
    "Key_H",
    "Key_I",
    "Key_J",
    "Key_K",
    "Key_L",
    "Key_M",
    "Key_N",
    "Key_O",
    "Key_P",
    "Key_Q",
    "Key_R",
    "Key_S",
    "Key_T",
    "Key_U",
    "Key_V",
    "Key_W",
    "Key_X",
    "Key_Y",
    "Key_Z",

    "Key_Minus",
    "Key_Plus",
    "Key_L_Bracket",
    "Key_R_Bracket",
    "Key_Backslash",
    "Key_Semicolon",
    "Key_Quote",
    "Key_Comma",
    "Key_Period",
    "Key_Slash",
    "Key_Tilde",
    "Key_Enter",

    "Key_CapsLock",
    "Key_L_Shift",
    "Key_L_Control",
    "Key_L_Alt",
    "Key_L_Windows",
    "Key_R_Shift",
    "Key_R_Control",
    "Key_R_Alt",
    "Key_R_Windows",
    "Key_Application",

    "Key_Backspace",
    "Key_Tab",
    "Key_Space",

    "Key_Delete",
    "Key_Insert",
    "Key_Home",
    "Key_End",
    "Key_PageUp",
    "Key_PageDown",

    "Key_Up",
    "Key_Down",
    "Key_Left",
    "Key_Right",

    "Key_PrintScreen",
    "Key_ScrollLock",
    "Key_PauseBreak",

    "Key_NumLock",
    "Key_Num0",
    "Key_Num1",
    "Key_Num2",
    "Key_Num3",
    "Key_Num4",
    "Key_Num5",
    "Key_Num6",
    "Key_Num7",
    "Key_Num8",
    "Key_Num9",
    "Key_NumDivide",
    "Key_NumMultiply",
    "Key_NumMinus",
    "Key_NumPlus",
    "Key_NumEnter",
    "Key_NumDecimal",

    "COUNT"
})