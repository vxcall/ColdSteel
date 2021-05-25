#include "dllmain.h"
#include <iostream>
void Detach()
{
    FREECONSOLE()
}

auto PrintSign() -> void {
    std::cout << std::endl;
    std::cout << "\033[94m CCCCC   OOOOO  LL      DDDDD     SSSSS  TTTTTTT EEEEEEE EEEEEEE LL     " << std::endl;
    std::cout << "CC    C OO   OO LL      DD  DD   SS        TTT   EE      EE      LL     " << std::endl;
    std::cout << "CC      OO   OO LL      DD   DD   SSSSS    TTT   EEEEE   EEEEE   LL  " << std::endl;
    std::cout << "CC    C OO   OO LL      DD   DD       SS   TTT   EE      EE      LL     " << std::endl;
    std::cout << " CCCCC   OOOO0  LLLLLLL DDDDDD    SSSSS    TTT   EEEEEEE EEEEEEE LLLLLLL\033[39m" << std::endl;
    std::cout << std::endl << std::endl;
}

auto PrintInformation(uintptr_t moduleBase, const std::vector<OffsetInfo>& offsetInfos) -> void {
   for (auto& oi : offsetInfos) {
       if (oi.type == "float") {
           std::optional<float*> dynamicAddress = GetDynamicAddress<float>(moduleBase, oi.vecOffset);
           if (dynamicAddress != std::nullopt) {
               std::cout << "\r\033[91m[-] " << oi.name << "       \033[39m-> " << *dynamicAddress.value() << "       " << std::endl;
           }
       } else if (oi.type == "int") {
           std::optional<int*> dynamicAddress = GetDynamicAddress<int>(moduleBase, oi.vecOffset);
           if (dynamicAddress != std::nullopt) {
               std::cout << "\r\033[91m[-] " << oi.name << "       \033[39m-> " << *dynamicAddress.value() << "       " << std::endl;
           }
       }
   }
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    PrintSign();
    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));

    std::vector<OffsetInfo> pointers;

    std::vector<DWORD> healthOffset = offset::m_health;
    healthOffset.insert(healthOffset.begin(), offset::dwLocalPlayer.begin(), offset::dwLocalPlayer.end());
    OffsetInfo health("Health", "float", healthOffset);
    pointers.push_back(health);

    std::vector<DWORD> staminaOffset = offset::m_stamina;
    staminaOffset.insert(staminaOffset.begin(), offset::dwLocalPlayer.begin(), offset::dwLocalPlayer.end());
    OffsetInfo stamina("Stamina", "float", staminaOffset);
    pointers.push_back(stamina);

    int estimatedLines = pointers.size();

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        PrintInformation(moduleBase, pointers);
        std::cout << "\033[" << estimatedLines << "F";
        Sleep(50);
    }
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    } else if (dwReason == DLL_PROCESS_DETACH && !lpReserved) {
        Detach();
    }
    return TRUE;
}