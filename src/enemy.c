#include "enemy.h"
#include "constants.h"
#include <math.h>

void update_enemy(Enemy *enemy, float deltaTime, Ball *ball)
{
  if (!enemy->alive)
    return;
  
  if (enemy->fly_pattern == LINEAR)
  {
    float step = enemy->linear.speed * deltaTime;
    enemy->center_pos.x += enemy->linear.direction.x * step;
    enemy->center_pos.y += enemy->linear.direction.y * step;
    enemy->linear.traveled += step;

    if (enemy->linear.traveled >= enemy->linear.distance)
    {
      enemy->linear.traveled = 0.0f;
      enemy->linear.direction.x = -enemy->linear.direction.x;
      enemy->linear.direction.y = -enemy->linear.direction.y;
    }
  }
  else if (enemy->fly_pattern == CIRCULAR)
  {
    enemy->circular.angle += enemy->circular.angular_speed * deltaTime;
    enemy->center_pos.x = enemy->circular.center.x + cosf(enemy->circular.angle) * enemy->circular.radius;
    enemy->center_pos.y = enemy->circular.center.y + sinf(enemy->circular.angle) * enemy->circular.radius;
  }
  else if (enemy->fly_pattern == INFINITE)
  {
    float radius_x = enemy->infinite.radius;
    float radius_y = enemy->infinite.radius / 2.0f;

    enemy->infinite.time_parameter += enemy->infinite.speed * deltaTime;

    if (enemy->infinite.time_parameter >= TWO_PI)
      enemy->infinite.time_parameter -= TWO_PI;
    else if (enemy->infinite.time_parameter < 0)
      enemy->infinite.time_parameter += TWO_PI;

    enemy->center_pos.x = enemy->infinite.center.x + radius_x * cosf(enemy->infinite.time_parameter);
    enemy->center_pos.y = enemy->infinite.center.y + radius_y * sinf(enemy->infinite.time_parameter);
  }

  if (CheckCollisionCircleRec(ball->center_pos, ball->radius, enemy->collision))
  {
    enemy->alive = false;
  }

  enemy->texture_pos.x = enemy->center_pos.x - (enemy->texture.width * enemy->scale / 2);
  enemy->texture_pos.y = enemy->center_pos.y - (enemy->texture.height * enemy->scale / 2);
  enemy->collision = (Rectangle){
    .x = enemy->texture_pos.x,
    .y = enemy->texture_pos.y,
    .width = enemy->texture.width * enemy->scale,
    .height = enemy->texture.height * enemy->scale,
  };
}

void init_enemy(Enemy *enemy, fly_position spawn_position, enemy_type type, enemy_fly_pattern fly_pattern)
{
  enemy->type = type;
  enemy->fly_pattern = fly_pattern;
  enemy->spawn_position = spawn_position;
  enemy->alive = true;
  enemy->texture = LoadTexture("assets/enemy.png");

  switch (spawn_position)
  {
    case TOP_LEFT:      enemy->center_pos = TOP_LEFT_SPAWN;     break;
    case TOP_RIGHT:     enemy->center_pos = TOP_RIGHT_SPAWN;    break;
    case CENTER:        enemy->center_pos = CENTER_SPAWN;       break;
    case BOTTOM_LEFT:   enemy->center_pos = BOTTOM_LEFT_SPAWN;  break;
    case BOTTOM_RIGHT:  enemy->center_pos = BOTTOM_RIGHT_SPAWN; break;
  }

  const EnemyConfig *cfg = &ENEMY_CONFIGS[type];

  switch (fly_pattern)
  {
    case LINEAR:
    {
      enemy->linear.speed = cfg->linear.speed;
      enemy->linear.distance = cfg->linear.distance;
      enemy->linear.traveled = 0.0f;

      float angle = cfg->linear.angle;
      enemy->linear.direction.x = cosf(angle);
      enemy->linear.direction.y = sinf(angle);

      float half = cfg->linear.distance / 2.0f;
      enemy->linear.start.x = enemy->center_pos.x - enemy->linear.direction.x * half;
      enemy->linear.start.y = enemy->center_pos.y - enemy->linear.direction.y * half;
      enemy->linear.end.x = enemy->center_pos.x + enemy->linear.direction.x * half;
      enemy->linear.end.y = enemy->center_pos.y + enemy->linear.direction.y * half;
      break;
    }
    case CIRCULAR:
    {
      enemy->circular.center = enemy->center_pos;
      enemy->circular.radius = cfg->circular.radius;
      enemy->circular.angular_speed = cfg->circular.angular_speed;
      enemy->circular.angle = 0.0f;
      break;
    }
    case INFINITE:
    {
      enemy->infinite.center = enemy->center_pos;
      enemy->infinite.radius = cfg->infinite.radius;
      enemy->infinite.speed = cfg->infinite.speed;
      enemy->infinite.time_parameter = 0.0f;
      break;
    }
  }

  switch (type)
  {
    case NORMAL:
      enemy->scale = ENEMY_SCALE_NORMAL;
      break;
    case PEST:
      enemy->scale = ENEMY_SCALE_PEST;
      break;
    case BUFF:
      enemy->scale = ENEMY_SCALE_BUFF;
      break;
    case ENEMY_TYPE_COUNT:
      enemy->scale = ENEMY_SCALE_NORMAL;
      break;
  }
  enemy->rotation = 0.0f;
  enemy->texture_pos.x = enemy->center_pos.x - (enemy->texture.width * enemy->scale / 2);
  enemy->texture_pos.y = enemy->center_pos.y - (enemy->texture.height * enemy->scale / 2);
  enemy->collision = (Rectangle){
    .x = enemy->texture_pos.x,
    .y = enemy->texture_pos.y,
    .width = enemy->texture.width * enemy->scale,
    .height = enemy->texture.height * enemy->scale,
  };
}