#pragma once

#include <vector>
#include <Windows.h>

namespace offset {
    //<Remnant-Win64-Shipping.exe>
    std::vector<DWORD> dwLocalPlayer = {0x03364D18, 0x0, 0x20};
    std::vector<DWORD> m_health = {0x870};
    std::vector<DWORD> m_stamina = {0xEA8, 0x140};
    std::vector<DWORD> m_xAxis = {0x3A0, 0x1A0};
    std::vector<DWORD> m_yzAxis = {0x3A0, 0x1A4};
    std::vector<DWORD> m_zAxis = {0x3A0, 0x1A8};
    std::vector<DWORD> m_pitch = {0xD10, 0xE3C};
    std::vector<DWORD> m_yaw = {0xD10, 0xE40};
    std::vector<DWORD> m_dragonHeart = {0x3364D18, 0x0, 0x20, 0x950, 0x1E8, 0x1A8, 0x2C};
    std::vector<DWORD> ammo = {0x3596E80, 0x30, 0x3c0, 0x4b0, 0x478, 0x2a8, 0x350, 0x54};
    std::vector<DWORD> skill = {0x3596E80, 0x30, 0x3C0, 0x4B0, 0x478, 0x2A8, 0xBB4};
}