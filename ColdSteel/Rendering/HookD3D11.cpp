#include "HookD3D11.h"
#include <iostream>

auto CreateD3D11SwapChainDeviceContext() -> std::tuple<bool, IDXGISwapChain*, ID3D11Device*, ID3D11DeviceContext*> {
    HWND hWnd = FindWindowA(nullptr, "Remnant  ");
    //Forward instantiation of swapChainDesc to create swapchain and device later on.
    DXGI_SWAP_CHAIN_DESC swapChainDesc{0};
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL featureLevel;
    IDXGISwapChain* pSwapChain;
    ID3D11Device* pDevice;
    ID3D11DeviceContext* pDeviceContext;

    HRESULT hResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pDeviceContext);
    if (FAILED(hResult)) {
        std::cout << "[Error] Failed Creating Device and SwapChain" << std::endl;
        return {false, pSwapChain, pDevice, pDeviceContext};
    }
    return  {true, pSwapChain, pDevice, pDeviceContext};
}

auto HookD3D11::Place() -> void {
    auto[status, pSwapChain, pDevice, pDeviceContext] = CreateD3D11SwapChainDeviceContext();
    if (status) {
        void** pSwapChainTable = *reinterpret_cast<void***>(pSwapChain);
        //create hkPresent
        //make oPresent = nullptr
        //something like Hook(pSwapChainTable[8], &hkPresent, &oPresent)
    }
}