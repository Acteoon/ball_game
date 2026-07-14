#include "modifier.h"
#include "raylib.h"
#include "enemy.h"


void init_enemy_modifiers(EnemyModifiers enemy_modifiers[])
{
    enemy_modifiers[NORMAL] = (EnemyModifiers){
        .projectile = {
            .speed     = { .add = 0.0f, .multiply = 1.0f },
            .fire_rate = { .add = 0.0f, .multiply = 1.0f },
            .radius    = { .add = 0.0f, .multiply = 1.0f },
        },
        .linear     = { .speed = { .add = 0.0f, .multiply = 1.0f } },
        .circular   = {
            .angular_speed = { .add = 0.0f, .multiply = 1.0f },
            .radius        = { .add = 0.0f, .multiply = 1.0f },
        },
        .infinite   = {
            .speed  = { .add = 0.0f, .multiply = 1.0f },
            .radius = { .add = 0.0f, .multiply = 1.0f },
        },
    };

    enemy_modifiers[PEST] = (EnemyModifiers){
        .projectile = {
            .speed     = { .add = 0.0f, .multiply = 1.0f },
            .fire_rate = { .add = 0.0f, .multiply = 1.0f },
            .radius    = { .add = 0.0f, .multiply = 1.0f },
        },
        .linear     = { .speed = { .add = 0.0f, .multiply = 1.0f } },
        .circular   = {
            .angular_speed = { .add = 0.0f, .multiply = 1.0f },
            .radius        = { .add = 0.0f, .multiply = 1.0f },
        },
        .infinite   = {
            .speed  = { .add = 0.0f, .multiply = 1.0f },
            .radius = { .add = 0.0f, .multiply = 1.0f },
        },
    };

    enemy_modifiers[BUFF] = (EnemyModifiers){
        .projectile = {
            .speed     = { .add = 0.0f, .multiply = 1.0f },
            .fire_rate = { .add = 0.0f, .multiply = 1.0f },
            .radius    = { .add = 0.0f, .multiply = 1.0f },
        },
        .linear     = { .speed = { .add = 0.0f, .multiply = 1.0f } },
        .circular   = {
            .angular_speed = { .add = 0.0f, .multiply = 1.0f },
            .radius        = { .add = 0.0f, .multiply = 1.0f },
        },
        .infinite   = {
            .speed  = { .add = 0.0f, .multiply = 1.0f },
            .radius = { .add = 0.0f, .multiply = 1.0f },
        },
    };
}

void init_player_modifiers(PlayerModifiers player_modifiers)
{
    player_modifiers.scale = (modifier){ .add = 0.0f, .multiply = 1.0f };
    player_modifiers.rotation = (modifier){ .add = 0.0f, .multiply = 1.0f };
    player_modifiers.speed = (modifier){ .add = 0.0f, .multiply = 1.0f };
}

void init_ball_modifiers(BallModifiers ball_modifiers)
{
    ball_modifiers.speed = (modifier){ .add = 0.0f, .multiply = 1.0f };
    ball_modifiers.radius = (modifier){ .add = 0.0f, .multiply = 1.0f };
    ball_modifiers.max_speed = (modifier){ .add = 0.0f, .multiply = 1.0f };
    ball_modifiers.min_speed = (modifier){ .add = 0.0f, .multiply = 1.0f };
}