#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "projectile.h"
#include "modifier.h"
#include <stdbool.h>
#include "ball.h"

typedef enum
{
  NORMAL,
  PEST,
  BUFF,
  ENEMY_TYPE_COUNT
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
} fly_position;

typedef struct
{
  float speed;
  float distance;
  float angle;
} LinearConfig;

typedef struct
{
  float radius;
  float angular_speed;
} CircularConfig;

typedef struct
{
  float radius;
  float speed;
} InfiniteConfig;

typedef struct
{
  LinearConfig   linear;
  CircularConfig circular;
  InfiniteConfig infinite;
} EnemyConfig;

typedef struct
{
  Vector2 start;
  Vector2 end;
  Vector2 direction;
  float speed;
  float distance;
  float traveled;
} linear_data;

typedef struct
{
  Vector2 center;
  float radius;
  float angular_speed;
  float angle;
} circular_data;

typedef struct
{
  Vector2 center;
  float radius;
  float time_parameter;
  float speed;
} infinite_data;

typedef struct
{
  Vector2 position;
  Vector2 direction;
  float speed;
  float scale;
  float fire_rate;
  float time_since_last_shot;
} projectile_data;

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

  linear_data linear;
  circular_data circular;
  infinite_data infinite;

  projectile_data projectile;

} Enemy;

void update_enemy(Enemy *enemy, float deltaTime, Ball *ball, EnemyModifiers *modifiers, Projectile *projectiles, Texture2D *projectile_texture);
void init_enemy(Enemy *enemy, fly_position spawn_position, enemy_type type, enemy_fly_pattern fly_pattern, Texture2D *textures);

#endif