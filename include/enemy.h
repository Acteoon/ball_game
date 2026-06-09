#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef enum 
{ 
  NORMAL, 
  PEST, 
  BUFF,
} enemy_type;

typedef enum
{ 
  LINEAR, 
  CIRCULAR, 
  INFINITE,
} enemy_fly_pattern;

typedef struct Enemy
{
  Texture texture;
  Vector2 center_pos;
  Vector2 texture_pos;
  float scale;
  float rotation;
  Vector2 speed;
  Rectangle collision;

  enemy_type type;
  enemy_fly_pattern fly_pattern;
} Enemy;

void update_enemy(Enemy *enemy, float deltaTime);

#endif
