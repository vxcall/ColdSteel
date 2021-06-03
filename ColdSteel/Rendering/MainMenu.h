#pragma once

#include "imgui.h"
#include "../GlobalFlags.h"
#include "../Rendering/ImGuiTheme.h"
#include "../Hook/D3D11/Present.h"
#include <string>
#include "../dllmain.h"
#include "../Entity.h"

namespace MainMenu {
    auto Render() -> void;
}

