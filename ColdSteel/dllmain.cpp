#include "dllmain.h"

Entity* localPlayer = nullptr;

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    auto moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));

    Hook::Init();
    HookD3D11::Place();

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;
        if (GetAsyncKeyState(VK_HOME) & 1) {
            Flags::showMenu = !Flags::showMenu;
        }
        localPlayer = GetDynamicAddress<Entity>(moduleBase, Offset::dwLocalPlayer);
        Sleep(50);
    }

    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

void Detach()
{
    Hook::Uninit();
    HookD3D11::UnhookWndProc();
    FREECONSOLE()
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