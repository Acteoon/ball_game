#include "enemy.h"
#include "ball.h"
#include "constants.h"
#include "modifier.h"
#include "projectile.h"
#include <math.h>

void update_enemy(Enemy *enemy, float deltaTime, Ball *ball, EnemyModifiers *modifiers, Projectile *projectiles, Texture2D *projectile_texture)
{
  int i;
  if (enemy->alive && CheckCollisionCircleRec(ball->center_pos, ball->radius, enemy->collision))
  {
    enemy->alive = false;
  }


  if (!enemy->alive)
    return;
  
  if (enemy->fly_pattern == LINEAR)
  {
    float step = (enemy->linear.speed + modifiers[enemy->type].linear.speed.add) * deltaTime * modifiers[enemy->type].linear.speed.multiply;
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
    float ang_speed = (enemy->circular.angular_speed + modifiers[enemy->type].circular.angular_speed.add) * modifiers[enemy->type].circular.angular_speed.multiply;
    enemy->circular.angle += ang_speed * deltaTime;

    if (enemy->circular.angle >= TWO_PI)
      enemy->circular.angle -= TWO_PI;
    else if (enemy->circular.angle < 0)
      enemy->circular.angle += TWO_PI;

    float radius = (enemy->circular.radius + modifiers[enemy->type].circular.radius.add) * modifiers[enemy->type].circular.radius.multiply;
    enemy->center_pos.x = enemy->circular.center.x + cosf(enemy->circular.angle) * radius;
    enemy->center_pos.y = enemy->circular.center.y + sinf(enemy->circular.angle) * radius;
  }
  else if (enemy->fly_pattern == INFINITE)
  {
    float radius_x = enemy->infinite.radius;
    float radius_y = enemy->infinite.radius / 2.0f;

    float inf_speed = (enemy->infinite.speed + modifiers[enemy->type].infinite.speed.add) * modifiers[enemy->type].infinite.speed.multiply;
    enemy->infinite.time_parameter += inf_speed * deltaTime;

    if (enemy->infinite.time_parameter >= TWO_PI)
      enemy->infinite.time_parameter -= TWO_PI;
    else if (enemy->infinite.time_parameter < 0)
      enemy->infinite.time_parameter += TWO_PI;

    float radius_x_eff = (radius_x + modifiers[enemy->type].infinite.radius.add) * modifiers[enemy->type].infinite.radius.multiply;
    float radius_y_eff = (radius_y + modifiers[enemy->type].infinite.radius.add) * modifiers[enemy->type].infinite.radius.multiply;
    enemy->center_pos.x = enemy->infinite.center.x + radius_x_eff * cosf(enemy->infinite.time_parameter);
    enemy->center_pos.y = enemy->infinite.center.y + radius_y_eff * sinf(enemy->infinite.time_parameter);
  }


  enemy->texture_pos.x = enemy->center_pos.x - (enemy->texture.width * enemy->scale / 2);
  enemy->texture_pos.y = enemy->center_pos.y - (enemy->texture.height * enemy->scale / 2);
  enemy->collision = (Rectangle){
    .x = enemy->texture_pos.x,
    .y = enemy->texture_pos.y,
    .width = enemy->texture.width * enemy->scale,
    .height = enemy->texture.height * enemy->scale,
  };

  enemy->projectile.time_since_last_shot += GetFrameTime();
  float eff_fire_rate = (enemy->projectile.fire_rate + modifiers[enemy->type].projectile.fire_rate.add) * modifiers[enemy->type].projectile.fire_rate.multiply;
  if(enemy->projectile.time_since_last_shot > eff_fire_rate)
  {
    for (i = 0; i < NUM_PROJECTILES; i++) 
    {
      if (!projectiles[i].active) 
      {
        /* apply projectile speed modifier so init_projectile reads the effective speed */
        float old_speed = enemy->projectile.speed;
        enemy->projectile.speed = (enemy->projectile.speed + modifiers[enemy->type].projectile.speed.add) * modifiers[enemy->type].projectile.speed.multiply;
        init_projectile(&projectiles[i], enemy, projectile_texture);
        enemy->projectile.speed = old_speed;
        break;  // Stop after initializing the first inactive one
      }
    }
    enemy->projectile.time_since_last_shot = 0.0f;
  }
}

void init_enemy(Enemy *enemy, fly_position spawn_position, enemy_type type, enemy_fly_pattern fly_pattern, Texture2D *textures)
{
  enemy->type = type;
  enemy->fly_pattern = fly_pattern;
  enemy->spawn_position = spawn_position;
  enemy->alive = true;

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
      enemy->texture = textures[NORMAL];
      enemy->projectile.fire_rate = ENEMY_FIRERATE_NORMAL;
      enemy->projectile.speed = ENEMY_PROJECTILE_SPEED_NORMAL;
      enemy->projectile.scale = ENEMY_PROJECTILE_SCALE_NORMAL;
      break;
    case PEST:
      enemy->scale = ENEMY_SCALE_PEST;
      enemy->texture = textures[PEST];
      enemy->projectile.fire_rate = ENEMY_FIRERATE_PEST;
      enemy->projectile.speed = ENEMY_PROJECTILE_SPEED_PEST;
      enemy->projectile.scale = ENEMY_PROJECTILE_SCALE_PEST;
      break;
    case BUFF:
      enemy->scale = ENEMY_SCALE_BUFF;
      enemy->texture = textures[BUFF];
      enemy->projectile.fire_rate = ENEMY_FIRERATE_BUFF;
      enemy->projectile.speed = ENEMY_PROJECTILE_SPEED_BUFF;
      enemy->projectile.scale = ENEMY_PROJECTILE_SCALE_BUFF;
      break;
    case ENEMY_TYPE_COUNT:
      enemy->scale = ENEMY_SCALE_NORMAL;
      break;
  }
  enemy->projectile.direction = (Vector2){ 0.0f, 1.0f };

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