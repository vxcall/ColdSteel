#pragma once

#include "MinHook.h"
#include <vector>

namespace Hook {
    auto Init() -> bool;
    auto Hook(LPVOID pTargetFunc, LPVOID pDetourFunc, LPVOID pOriginalFunc) -> bool;
    auto Uninit() -> void;
}