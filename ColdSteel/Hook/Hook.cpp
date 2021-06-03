#include "Hook.h"

namespace Hook {
    std::vector<void*> originalFuncs;
}

auto Hook::Init() -> bool {
    if (MH_Initialize() != MH_OK)
    {
        return false;
    } else {
        return true;
    }
}

auto Hook::Hook(LPVOID& pTargetFunc, LPVOID pDetourFunc, LPVOID pOriginalFunc) -> bool {
    if (MH_CreateHook(pTargetFunc, pDetourFunc, reinterpret_cast<LPVOID*>(pOriginalFunc)) == MH_OK) {
        if (MH_EnableHook(pTargetFunc) == MH_OK) {
            Hook::originalFuncs.push_back(pOriginalFunc);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

auto Hook::Restore() -> void {
    for (auto& org : Hook::originalFuncs)
    {
        MH_DisableHook(org);
    }
    MH_Uninitialize();
}