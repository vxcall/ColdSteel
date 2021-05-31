#include "Present.h"
#include <iostream>


namespace HookD3D11 {
    HWND hWnd = nullptr;
    //Save pSwapChain for v-table hooking
    IDXGISwapChain* pSwapChain = nullptr;
    //Save pDevice and pDeviceContext for initializing imgui
    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pDeviceContext = nullptr;
    ID3D11RenderTargetView*  pRenderTargetView = NULL;
}

auto CreateD3D11SwapChainDeviceContext() -> bool {
    HookD3D11::hWnd = FindWindowA(nullptr, "Remnant  ");
    //Forward instantiation of swapChainDesc to create swapchain and device later on.
    DXGI_SWAP_CHAIN_DESC swapChainDesc{0};
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = HookD3D11::hWnd;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &HookD3D11::pSwapChain, &HookD3D11::pDevice, &featureLevel, &HookD3D11::pDeviceContext);
    if (FAILED(hResult)) {
        std::cout << "[Error] Failed Creating Device and SwapChain" << std::endl;
        return false;
    }
    return  true;
}

using tPresent = HRESULT(__thiscall*) (IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
tPresent oPresent = nullptr;

auto __fastcall hkPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags) -> HRESULT {
    static std::once_flag isInited;
    std::call_once(isInited, [&]() {
        //Replacing pSwapChain, pDevice and pDeiceContext to the ones the game is actually using
        HookD3D11::pSwapChain = pThis;
        if (SUCCEEDED(HookD3D11::pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)&HookD3D11::pDevice))) {
            HookD3D11::pDevice->GetImmediateContext(&HookD3D11::pDeviceContext);
        }
        HookD3D11::HookWndProc();
        Menu::InitImGui();
    });

    Menu::Render();

    return oPresent(pThis, SyncInterval, Flags);
}

auto HookD3D11::Place() -> void {
    bool status = CreateD3D11SwapChainDeviceContext();
    if (status) {
        void** pSwapChainTable = *reinterpret_cast<void***>(HookD3D11::pSwapChain);
        Hook::Hook(pSwapChainTable[8], &hkPresent, &oPresent);
    }
}