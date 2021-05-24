#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include <optional>
#include "offset.h"

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

class OffsetInfo {
public:
    std::string name;
    std::string type;
    std::vector<DWORD> vecOffset;
};

template <typename T>
auto GetDynamicAddress(uintptr_t& moduleBase, std::vector<DWORD> offsets) -> std::optional<T*> {
    uintptr_t base = *reinterpret_cast<uintptr_t*>(moduleBase + offsets.at(0));
    std::optional<T*> result;
    offsets.erase(offsets.begin());
    for (short i=0; i<offsets.size(); ++i) {
        if (!base) {
            return {};
        }
        if (i != offsets.size()-1) {
            base = *reinterpret_cast<uintptr_t*>(base+offsets.at(i));
        } else {
            result = reinterpret_cast<T*>(base + offsets.at(i));
        }
    }
    return result;
}
