#pragma once

#include <Windows.h>
#include <utility>
#include <vector>
#include <optional>
#include "Offset.h"
#include "Entity.h"
#include "Hook.h"
#include "HookD3D11/Present.h"
#include "HookD3D11/WndProc.h"

#define DEBUG

#ifdef DEBUG
#define LOGHEX(name, val) std::cout << name << ": " << std::hex << val << std::endl;
#define LOG(name, val) std::cout << name << ": " << val << std::endl;
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
#define LOGHEX(name, val)
#define LOG(name, val)
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif

template<typename T>
auto GetDynamicAddress(const uintptr_t moduleBase, std::vector<uintptr_t> offsets) -> T* {
     uintptr_t dummy = *reinterpret_cast<uintptr_t*>(moduleBase + offsets.at(0));

    if (!dummy)
        return nullptr;

    T* result;

    offsets.erase(offsets.begin());

    for (short i=0; i<offsets.size(); ++i) {
        if (i != offsets.size()-1) {
            dummy = *reinterpret_cast<uintptr_t*>(dummy+offsets.at(i));
        } else {
            result = reinterpret_cast<T*>(dummy + offsets.at(i));
        }

        if (!dummy)
          return nullptr;
    }

    return reinterpret_cast<T*>(result);
}
