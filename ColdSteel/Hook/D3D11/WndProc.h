#pragma once

#include "imgui_impl_win32.h"
#include "imgui.h"
#include <Windows.h>
#include "Present.h"
#include "../../HackFlags.h"

namespace HookD3D11 {
    extern WNDPROC oWndProc;
    auto WINAPI hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
    auto UnhookWndProc() -> void;
    auto HookWndProc() -> void;
}