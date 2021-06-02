#pragma once
#include "Utils.h"
#include <vector>
#include "Vectors.h"
#include "Modules.h"
#include "Offset.h"
#include "Utils.h"

class Movement
{
public:
    union {
        DEFINE_MEMBER_0(void* base, 0x0);
        DEFINE_MEMBER_N(Vector3 position, 0x01A0);
    };
}; //Size: 0x01AC

class StaminaClass
{
public:
    union {
        DEFINE_MEMBER_0(void* base, 0x0);
        DEFINE_MEMBER_N(float stamina, 0x0140);
    };
}; //Size: 0x0144


class View
{
public:
    union {
        DEFINE_MEMBER_0(void* base, 0x0);
        DEFINE_MEMBER_N(Vector2 angle, 0x0E3C);
    };
}; //Size: 0x0E44

class Entity
{
public:
    union {
        DEFINE_MEMBER_0(void* base, 0x0);
        DEFINE_MEMBER_N(bool isEnemy, 0x50);
        DEFINE_MEMBER_N(Movement* movement, 0x03A0);
        DEFINE_MEMBER_N(float health, 0x0870);
        DEFINE_MEMBER_N(View* view, 0x0D10);
        DEFINE_MEMBER_N(StaminaClass* staminaClass, 0x0EA8);
    };
}; //Size: 0x1080

auto GetEnemies() -> std::vector<Entity*>;
