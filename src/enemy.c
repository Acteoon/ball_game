#include "enemy.h"
#include "constants.h"
#include <math.h>

void update_enemy(Enemy *enemy, float deltaTime)
{
  if( enemy->fly_pattern == LINEAR )
  {
    enemy->linear_data.direction.x = enemy->linear_data.end.x - enemy->linear_data.start.x;
    enemy->linear_data.direction.y = enemy->linear_data.end.y - enemy->linear_data.start.y;
    enemy->linear_data.distance = sqrtf(enemy->linear_data.direction.x * enemy->linear_data.direction.x + enemy->linear_data.direction.y * enemy->linear_data.direction.y);
    if (enemy->linear_data.distance != 0) 
    {
      enemy->linear_data.direction.x /= enemy->linear_data.distance;
      enemy->linear_data.direction.y /= enemy->linear_data.distance;
    }
    enemy->center_pos.x += enemy->linear_data.direction.x * enemy->linear_data.speed * deltaTime;
    enemy->center_pos.y += enemy->linear_data.direction.y * enemy->linear_data.speed * deltaTime;

    float distance_traveled = sqrtf((enemy->center_pos.x - enemy->linear_data.start.x) * (enemy->center_pos.x - enemy->linear_data.start.x) + (enemy->center_pos.y - enemy->linear_data.start.y) * (enemy->center_pos.y - enemy->linear_data.start.y));
    
    if (distance_traveled >= enemy->linear_data.distance) 
    {
      Vector2 temp = enemy->linear_data.start;
      enemy->linear_data.start = enemy->linear_data.end;
      enemy->linear_data.end = temp;
    }
  }
  else if( enemy->fly_pattern == CIRCULAR )
  {
    enemy->circular_data.angle += enemy->circular_data.angular_speed * deltaTime;
    enemy->center_pos.x = enemy->circular_data.center.x + cosf(enemy->circular_data.angle) * enemy->circular_data.radius;
    enemy->center_pos.y = enemy->circular_data.center.y + sinf(enemy->circular_data.angle) * enemy->circular_data.radius;
  }
  else if( enemy->fly_pattern == INFINITE )
  {

    float radius_x = enemy->infinite_data.radius;
    float radius_y = enemy->infinite_data.radius / 2; // Elliptical path

    enemy->infinite_data.time_parameter += enemy->infinite_data.speed * deltaTime;

    if (enemy->infinite_data.time_parameter >= TWO_PI) 
      enemy->infinite_data.time_parameter -= TWO_PI;
    else if (enemy->infinite_data.time_parameter < 0) 
      enemy->infinite_data.time_parameter += TWO_PI;

    enemy->center_pos.x = enemy->infinite_data.center.x + radius_x * cosf(enemy->infinite_data.time_parameter);
    enemy->center_pos.y = enemy->infinite_data.center.y + radius_y * sinf(enemy->infinite_data.time_parameter);
  }

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
    case TOP_LEFT:
      enemy->center_pos = TOP_LEFT_SPAWN;
      break;
    case TOP_RIGHT:
      enemy->center_pos = TOP_RIGHT_SPAWN;
      break;
    case CENTER:
      enemy->center_pos = CENTER_SPAWN;
      break;
    case BOTTOM_LEFT:
      enemy->center_pos = BOTTOM_LEFT_SPAWN;
      break;
    case BOTTOM_RIGHT:
      enemy->center_pos = BOTTOM_RIGHT_SPAWN;
      break;
  }

  switch (type) 
  {
      case NORMAL:
        switch(fly_pattern)
        {
          case LINEAR:
            enemy->linear_data.speed = ENEMY_LINEAR_SPEED_NORMAL;
            break;
          case CIRCULAR:
            enemy->circular_data.radius = ENEMY_CIRCULAR_RADIUS_NORMAL;
            enemy->circular_data.angular_speed = ENEMY_CIRCULAR_SPEED_NORMAL;
            enemy->circular_data.angle = 0.0f;
            break;
          case INFINITE:
            enemy->infinite_data.radius = ENEMY_INFINITE_RADIUS_NORMAL;
            enemy->infinite_data.speed = ENEMY_INFINITE_SPEED_NORMAL;
            enemy->infinite_data.time_parameter = 0.0f;
            break;
        }
        break;
      
      case PEST:
        switch(fly_pattern)
        {
          case LINEAR:
            enemy->linear_data.speed = ENEMY_LINEAR_SPEED_PEST;
            break;
          case CIRCULAR:
            enemy->circular_data.radius = ENEMY_CIRCULAR_RADIUS_PEST;
            enemy->circular_data.angular_speed = ENEMY_CIRCULAR_SPEED_PEST;
            enemy->circular_data.angle = 0.0f;
            break;
          case INFINITE:
            enemy->infinite_data.radius = ENEMY_INFINITE_RADIUS_PEST;
            enemy->infinite_data.speed = ENEMY_INFINITE_SPEED_PEST;
            enemy->infinite_data.time_parameter = 0.0f;
            break;
        }
        break;

      case BUFF:
        switch(fly_pattern)
        {
          case LINEAR:
            enemy->linear_data.speed = ENEMY_LINEAR_SPEED_BUFF;
            break;
          case CIRCULAR:
            enemy->circular_data.radius = ENEMY_CIRCULAR_RADIUS_BUFF;
            enemy->circular_data.angular_speed = ENEMY_CIRCULAR_SPEED_BUFF;
            enemy->circular_data.angle = 0.0f;
            break;
          case INFINITE:
            enemy->infinite_data.radius = ENEMY_INFINITE_RADIUS_BUFF;
            enemy->infinite_data.speed = ENEMY_INFINITE_SPEED_BUFF;
            enemy->infinite_data.time_parameter = 0.0f;
            break;
        }
        break;
  }
  
  enemy->scale = ENEMY_SCALE;
  enemy->rotation = 0.0f;
  enemy->texture_pos.x = enemy->center_pos.x - (enemy->texture.width * enemy->scale / 2);
  enemy->texture_pos.y = enemy->center_pos.y - (enemy->texture.height * enemy->scale / 2);
  enemy->collision = (Rectangle){ .x = enemy->texture_pos.x, .y = enemy->texture_pos.y, .width = enemy->texture.width * enemy->scale, .height = enemy->texture.height * enemy->scale };
}