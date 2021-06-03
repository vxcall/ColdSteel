#include "dllmain.h"

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()
    Modules::Initialize();
    Hook::Init();
    HookD3D11::Place();
    while (true) {
        if (GetAsyncKeyState (VK_DELETE) & 1) break;
        Sleep(50);
    }
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

void Detach()
{
    Hook::Restore();
    HookD3D11::RestoreWndProc();
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