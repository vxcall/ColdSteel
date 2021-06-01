#include "MainMenu.h"

auto MainMenu::Render() -> void {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (Flags::showMenu) {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar;
        windowFlags |= ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Cold Steel", &Flags::showMenu, windowFlags);
        ImGui::Text("Health -> ");
        ImGui::SameLine();
        ImGui::Text("%s", std::to_string(localPlayer->health).c_str());
        ImGui::Spacing();
        ImGui::Text("Stamina -> ");
        ImGui::SameLine();
        ImGui::Text("%s", std::to_string(localPlayer->staminaClass->stamina).c_str());
        ImGui::End();
    }
    ImGui::EndFrame();
    ImGui::Render();
    HookD3D11::pDeviceContext->OMSetRenderTargets(1, &HookD3D11::pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}




