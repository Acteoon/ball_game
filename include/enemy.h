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

typedef enum
{
  TOP_LEFT,
  TOP_RIGHT,
  CENTER,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,

}fly_position;


typedef struct 
{
  Vector2 center;
  float radius;
  float angular_speed;
  float angle;
}circular_data;

typedef struct
{
  Vector2 start;
  Vector2 end;
  float speed;
  int distance;
  Vector2 direction;
}linear_fly_pattern_data;

typedef struct
{
  Vector2 center;
  float radius; //also offset from center to the center of each circle
  float time_parameter;
  float speed;
}infinite_fly_pattern_data;

typedef struct Enemy
{
  Texture texture;
  Vector2 center_pos;
  Vector2 texture_pos;
  float scale;
  float rotation;
  Rectangle collision;
  bool alive;

  fly_position spawn_position;

  enemy_type type;
  enemy_fly_pattern fly_pattern;
  circular_data circular_data;
  linear_fly_pattern_data linear_data;
  infinite_fly_pattern_data infinite_data;
} Enemy;

void update_enemy(Enemy *enemy, float deltaTime);
void init_enemy(Enemy *enemy, fly_position spawn_position, enemy_type type, enemy_fly_pattern fly_pattern);

#endif
