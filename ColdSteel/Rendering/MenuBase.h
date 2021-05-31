#pragma once

#include "imgui.h"
#include "../Hook/D3D11/Present.h"
#include "../Rendering/ImGuiTheme.h"

namespace Menu {
    auto Render() -> void;
    auto InitImGui() -> void;
}

