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

typedef struct 
{
  Vector2 center;
  float radius;
  float angular_speed;
  float angle;
}circular_fly_pattern_data;

typedef struct
{
  Vector2 start;
  Vector2 end;
  float speed;
  int distance;
  Vector2 direction;
}linear_fly_pattern_data;

typedef struct Enemy
{
  Texture texture;
  Vector2 center_pos;
  Vector2 texture_pos;
  float scale;
  float rotation;
  Rectangle collision;

  enemy_type type;
  enemy_fly_pattern fly_pattern;
  circular_fly_pattern_data circular_fly_pattern_data;
  linear_fly_pattern_data linear_fly_pattern_data;
} Enemy;

void update_enemy(Enemy *enemy, float deltaTime);

#endif
