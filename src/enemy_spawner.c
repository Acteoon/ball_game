#include "enemy_spawner.h"
#include "raylib.h"
#include "constants.h"

void spawn_enemys(Enemy enemy[], Enemy_spawner *enemy_spawner, Texture2D *enemy_textures)
{
    int i = 0;
    fly_position fly_pos = GetRandomValue(0, 4);
    enemy_type enemy_typ =  GetRandomValue(0, 2);
    enemy_fly_pattern enemy_fly_pat = GetRandomValue(0, 2);


    enemy_spawner->time += GetFrameTime();  
    enemy_spawner->time_for_next_spawn = (enemy_spawner->time_for_next_spawn == 0) ? 
        (float)(GetRandomValue(ENEMY_SPAWN_TIME_MIN, ENEMY_SPAWN_TIME_MAX) * 0.01f) : 
        enemy_spawner->time_for_next_spawn;

    if (enemy_spawner->time > enemy_spawner->time_for_next_spawn)
    {
        for (i = 0; i < ENEMY_COUNT; i++)
        {
            if (!enemy[i].alive)
            {
                init_enemy(&enemy[i], fly_pos, enemy_typ, enemy_fly_pat, enemy_textures);
                enemy_spawner->time_for_next_spawn = 0;
                enemy_spawner->time = 0;
                break;
            }
        }
    }
}