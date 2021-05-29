#include "WndProc.h"
#include <iostream>

namespace HookD3D11 {
    WNDPROC originalWndProc;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

  auto WINAPI HookD3D11::hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }
    return CallWindowProc(HookD3D11::originalWndProc, hWnd, msg, wParam, lParam);
}

