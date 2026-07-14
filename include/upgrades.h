#ifndef EVENTS_H
#define EVENTS_H
#include "comon.h"

typedef struct
{
    bool active;
    int chance_percentage;
}Chance;

typedef struct
{
    bool active;
    int quantity;
}Value;

typedef struct
{
    bool player_move_with_mouse;
    bool player_kill_enemy_on_collision;

    bool ball_kill_projectiles;
    bool heart_on_ball_touch_ground;
    Chance ball_dublicate_on_enemy;
    Value ball_homming;
    
}Upgrades;

#endif // EVENTS_H