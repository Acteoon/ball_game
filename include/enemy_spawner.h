#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "raylib.h"
#include "constants.h"

typedef struct 
{
    float time;
    float time_for_next_spawn;
}Enemy_spawner;

void spawn_enemys(Enemy enemy[], Enemy_spawner *enemy_spawner, Texture2D *enemy_textures);

#endif