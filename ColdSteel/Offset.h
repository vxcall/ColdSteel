#pragma once

#include <vector>
#include <Windows.h>

namespace offset {
    //<Remnant-Win64-Shipping.exe>
    std::vector<uintptr_t> dwLocalPlayer = {0x03364D18, 0x0, 0x20, 0x0};
    std::vector<uintptr_t> dwEntityList = {0x032203D0, 0x0};
    std::vector<uintptr_t> ammo = {0x3596E80, 0x30, 0x3c0, 0x4b0, 0x478, 0x2a8, 0x350, 0x54};
    std::vector<uintptr_t> skill = {0x3596E80, 0x30, 0x3C0, 0x4B0, 0x478, 0x2A8, 0xBB4};
}