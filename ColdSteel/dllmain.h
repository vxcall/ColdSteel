#pragma once
#include <Windows.h>
#include <utility>
#include <vector>
#include <iostream>
#include <optional>
#include "Offset.h"
#include "Entity.h"

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
    OffsetInfo(std::string name, std::string type, std::vector<uintptr_t>& vecOffset) : name(std::move(name)), type(std::move(type)), vecOffset(std::move(vecOffset)) {
    }
    std::string name;
    std::string type;
    std::vector<uintptr_t> vecOffset;
};

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
