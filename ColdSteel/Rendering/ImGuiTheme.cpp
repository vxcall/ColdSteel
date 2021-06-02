#include "ImGuiTheme.h"

auto LoadFont(ImGuiIO io) -> void {
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/calibrib.ttf", 13);
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/calibrib.ttf", 11);
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/calibrib.ttf", 15);
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/calibrib.ttf", 19);
}
