#pragma once

#include "imgui_impl_win32.h"
#include "imgui.h"
#include <Windows.h>
#include "Present.h"

namespace HookD3D11 {
    extern WNDPROC originalWndProc;
    auto WINAPI hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
}