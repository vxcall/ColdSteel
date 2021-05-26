#include "dllmain.h"

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

auto PrintInformation(uintptr_t moduleBase, std::vector<OffsetInfo>& offsetInfos) -> void {
   for (auto& oi : offsetInfos) {
       if (oi.type == "float") {
           float* dynamicAddress = GetDynamicAddress<float>(moduleBase, oi.vecOffset);
           if (dynamicAddress) {
               std::cout << "\r\033[91m[-] " << oi.name << "       \033[39m-> " << *dynamicAddress << "       " << std::endl;
           }
       } else if (oi.type == "int") {
           int* dynamicAddress = GetDynamicAddress<int>(moduleBase, oi.vecOffset);
           if (dynamicAddress) {
               std::cout << "\r\033[91m[-] " << oi.name << "       \033[39m-> " << *dynamicAddress << "       " << std::endl;
           }
       }
   }
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    PrintSign();
    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));

    //int estimatedLines = pointers.size();

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        auto* localPlayer = GetDynamicAddress<Entity>(moduleBase, offset::dwLocalPlayer);
        if (localPlayer) {
            std::cout << localPlayer->view->angle.x << std::endl;
        }
        //PrintInformation(moduleBase, pointers);
        //std::cout << "\033[" << estimatedLines << "F";
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