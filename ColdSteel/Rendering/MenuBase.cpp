#include "MenuBase.h"

auto Menu::Render() -> void {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (HackFlags::showMenu) {
        ImGui::Begin("Cold Steel");
        ImGui::Text("Hack menu");
        ImGui::End();
    }
    ImGui::EndFrame();
    ImGui::Render();
    HookD3D11::pDeviceContext->OMSetRenderTargets(1, &HookD3D11::pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

auto CreateRenderTarget() -> void {
    ID3D11Texture2D* pBackBuffer;
    HookD3D11::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    HookD3D11::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &HookD3D11::pRenderTargetView);
    pBackBuffer->Release();
}

auto CleanupRenderTarget() -> void {
    if (HookD3D11::pRenderTargetView) { HookD3D11::pRenderTargetView->Release(); HookD3D11::pRenderTargetView = NULL; }
}

auto Menu::InitImGui() -> void {
    if (HookD3D11::hWnd) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        LoadFont(io);
        LoadTheme();
        ImGui_ImplWin32_Init(HookD3D11::hWnd);
        ImGui_ImplDX11_Init(HookD3D11::pDevice, HookD3D11::pDeviceContext);
        CreateRenderTarget();
    }
}


