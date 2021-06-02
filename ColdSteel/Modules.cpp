#include "Modules.h"

namespace Modules
{
    uintptr_t remnantBase;

    void Initialize()
    {
        remnantBase = reinterpret_cast<uintptr_t>(GetModuleHandle("Remnant-Win64-Shipping.exe"));
    }
}
