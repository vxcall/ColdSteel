#pragma once
#include <vector>

#define STR_MERGE_IMPL(x, y)                x##y
#define STR_MERGE(x,y)                        STR_MERGE_IMPL(x,y)
#define MAKE_PAD(size)                        BYTE STR_MERGE(pad_, __COUNTER__) [ size ]

#define DEFINE_MEMBER_0(x, y)                x
#define DEFINE_MEMBER_N(x,offset)            struct { MAKE_PAD(offset); x; }

auto IsBadReadPtr(void* p) -> bool;

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