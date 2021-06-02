#pragma once

#include <Windows.h>
#include <utility>
#include "Utils.h"
#include "Entity.h"
#include "Offset.h"
#include "Hook/Hook.h"
#include "Hook/D3D11/Present.h"
#include "Hook/D3D11/WndProc.h"
#include "GlobalFlags.h"
#include "Modules.h"

extern Entity* localPlayer;

#define DEBUG

#ifdef DEBUG
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif


