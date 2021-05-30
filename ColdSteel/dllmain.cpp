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

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    PrintSign();
    //auto moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));
    Hook::Init();
    HookD3D11::Place();

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        //auto* localPlayer = GetDynamicAddress<Entity>(moduleBase, offset::dwLocalPlayer);
        Sleep(50);
    }
    Hook::Uninit();
    SetWindowLongPtr(HookD3D11::hWnd, GWLP_WNDPROC, (LONG_PTR)HookD3D11::originalWndProc);
    FREECONSOLE()
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