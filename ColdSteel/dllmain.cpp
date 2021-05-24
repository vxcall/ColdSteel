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
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
}

auto PrintFloatInfo(uintptr_t moduleBase, const std::vector<OffsetInfo>& offsetInfos) -> void {
   int estimatedLines = offsetInfos.size();
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
   std::cout << "\033[" << estimatedLines + 1 << "F";
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    PrintSign();
    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        std::cout << "\033[9F";
        std::vector<DWORD> localPlayer = {0x03364D18, 0x0, 0x20};
        localPlayer.insert(localPlayer.end(), offset::m_health.begin(), offset::m_health.end());
        if (std::optional<float*> health = GetDynamicAddress<float>(moduleBase, localPlayer); health != std::nullopt) {
            std::cout << "\r\033[91m[-] Health       \033[39m-> " << *health.value() << "        " << std::endl;
        }

        if (std::optional<float*> stamina = GetDynamicAddress<float>(moduleBase, offset::m_stamina); stamina != std::nullopt) {
            std::cout << "\r\033[91m[-] Stamina      \033[39m-> " << *stamina.value() << "       " << std::endl;
        }

        if (std::optional<float*> zAxis = GetDynamicAddress<float>(moduleBase, offset::m_zAxis); zAxis != std::nullopt) {
            auto xAxis = reinterpret_cast<float *>(reinterpret_cast<uintptr_t>(*zAxis)-0x4);
            auto yAxis = reinterpret_cast<float *>(reinterpret_cast<uintptr_t>(*zAxis)-0x8);
            std::cout << "\r\033[91m[-] X axis        \033[39m-> " << *xAxis << "         " << std::endl;
            std::cout << "\r\033[91m[-] Y axis        \033[39m-> " << *yAxis << "         " << std::endl;
            std::cout << "\r\033[91m[-] Z axis        \033[39m-> " << *zAxis.value() << "         " << std::endl;
        }

        if (std::optional<float*> pitch = GetDynamicAddress<float>(moduleBase, offset::m_pitch); pitch != std::nullopt) {
            std::cout << "\r\033[91m[-] Pitch        \033[39m-> " << *pitch.value() << "         " << std::endl;
            //need to cast to uintptr_t beforehand otherwise the calculation will be messed up.
            auto yaw = reinterpret_cast<float *>(reinterpret_cast<uintptr_t >(*pitch)+0x4);
            std::cout << "\r\033[91m[-] Yaw          \033[39m-> " << *yaw << "      " << std::endl;

        }

        if (std::optional<int*> ammo = GetDynamicAddress<int>(moduleBase, offset::ammo); ammo != std::nullopt) {
            std::cout << "\r\033[91m[-] Current Ammo \033[39m-> " << *ammo.value() << "      " << std::endl;
        }

        if (std::optional<int*> skill = GetDynamicAddress<int>(moduleBase, offset::skill); skill != std::nullopt) {
            std::cout << "\r\033[91m[-] Skill \033[39m-> " << *skill.value() << "       " << std::endl;
        }

        if (std::optional<int*> dragonHeart = GetDynamicAddress<int>(moduleBase, offset::m_dragonHeart); dragonHeart != std::nullopt) {
            std::cout << "\r\033[91m[-] Remaining Dragon heart \033[39m-> " << *dragonHeart.value() << "       ";
        }
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