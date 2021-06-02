#pragma once

#include "imgui_impl_win32.h"
#include "imgui.h"
#include <Windows.h>
#include "Present.h"
#include "../../GlobalFlags.h"

namespace HookD3D11 {
    extern WNDPROC oWndProc;
    auto WINAPI hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
    auto RestoreWndProc() -> void;
    auto HookWndProc() -> void;
}