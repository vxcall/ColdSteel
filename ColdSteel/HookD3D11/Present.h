#pragma once
#include <D3D11.h>
#include <tuple>
#include <mutex>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "../Hook.h"
#include "WndProc.h"
#include "../HackFlags.h"

namespace HookD3D11 {
    auto Place() -> void;
    auto InitImgui() -> void;
    auto CreateRenderTarget() -> void;
    auto CleanupRenderTarget() -> void;
    extern HWND hWnd;
    extern IDXGISwapChain* pSwapChain;
    extern ID3D11Device* pDevice;
    extern ID3D11DeviceContext* pDeviceContext;
}