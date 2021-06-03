#include "Entity.h"
#include <iostream>

auto GetLocalPlayer() -> Entity* {
    return GetDynamicAddress<Entity>(Modules::remnantBase, Offset::dwLocalPlayer);
}

auto GetEnemies() -> std::vector<Entity*> {
    const short maxEntity = 46;
    std::vector<Entity*> result;
    const uintptr_t entityListBase = reinterpret_cast<uintptr_t>(GetDynamicAddress<uintptr_t>(Modules::remnantBase, Offset::dwEntityList));
    auto* localPlayer = GetLocalPlayer();
    for (short i = 0; i<maxEntity; ++i) {
        //0x18 is the gap between each entity.
        auto targetMemoryRegion = reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(entityListBase + i * 0x18));
        //Checking whether the Address is the pointer or just random numbers.
        if (!IsBadReadPtr(targetMemoryRegion)) {
            auto ent = reinterpret_cast<Entity*>(targetMemoryRegion);
            //Checking if the candidates are actually an enemy.
            if (ent->isEnemy && ent != localPlayer) {
                result.push_back(ent);
            }
        }
    }
    return result;
}

auto Entity::FreezeHealth() -> void {
    this->health = 1000;
}

auto Entity::FreezeStamina() -> void {
    this->staminaClass->stamina = 175;
}
