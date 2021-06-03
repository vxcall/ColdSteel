#include "MainMenu.h"

auto MainMenu::Render() -> void {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    auto localPlayer = GetLocalPlayer();
    if (Flags::freezeHealth) {
        localPlayer->FreezeHealth();
    }
    if (Flags::freezeStamina) {
        localPlayer->FreezeStamina();
    }
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    if (Flags::showMenu) {

        ImGui::Begin("Cold Steel", &Flags::showMenu, windowFlags);

        ImGui::Checkbox("Freeze Health", &Flags::freezeHealth);
        ImGui::SliderFloat("Health", &localPlayer->health, 1, 1000);
        ImGui::Spacing();
        ImGui::Checkbox("Freeze Stamina", &Flags::freezeStamina);
        ImGui::SliderFloat("Stamina", &localPlayer->staminaClass->stamina, 1, 175);
        ImGui::Spacing();
        ImGui::Checkbox("Show entity list", &Flags::showEntityListMenu);

        ImGui::End();
    }
    if (Flags::showEntityListMenu) {
        ImGui::Begin("Entity list", &Flags::showEntityListMenu, ImGuiWindowFlags_NoCollapse);
        auto&& enemyList = GetEnemies();
        int numEnt = 1;
        for (auto& enemy : enemyList) {
            char title[10];
            snprintf(title, 10, "%s %s", "Enemy", std::to_string(numEnt).c_str());
            if (ImGui::TreeNode(title)) {
                ImGui::Text("%x", enemy->ID);
                ImGui::Text("%s", std::to_string(enemy->health).c_str());
                ImGui::TreePop();
            }
            ++numEnt;
        }

        ImGui::End();
    }
    ImGui::EndFrame();
    ImGui::Render();
    HookD3D11::pDeviceContext->OMSetRenderTargets(1, &HookD3D11::pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}