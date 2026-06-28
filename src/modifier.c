#include "modifier.h"
#include "raylib.h"
#include "enemy.h"


void init_enemy_modifiers(EnemyModifiers enemy_modifiers[])
{
    enemy_modifiers[NORMAL] = (EnemyModifiers){
        .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
        .linear     = { .speed = 1.0f },
        .circular   = { .angular_speed = 1.0f, .radius = 1.0f },
        .infinite   = { .speed = 1.0f, .radius = 1.0f },
    };

    enemy_modifiers[PEST] = (EnemyModifiers){
        .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
        .linear     = { .speed = 1.0f },
        .circular   = { .angular_speed = 1.0f, .radius = 1.0f },
        .infinite   = { .speed = 1.0f, .radius = 1.0f },
    };

    enemy_modifiers[BUFF] = (EnemyModifiers){
        .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
        .linear     = { .speed = 1.0f },
        .circular   = { .angular_speed = 1.0f, .radius = 1.0f },
        .infinite   = { .speed = 1.0f, .radius = 1.0f },
    };
}
