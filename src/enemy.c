#include "enemy.h"
#include <math.h>

void update_enemy(Enemy *enemy, float deltaTime)
{
  if( enemy->fly_pattern == LINEAR )
  {
    enemy->linear_fly_pattern_data.direction.x = enemy->linear_fly_pattern_data.end.x - enemy->linear_fly_pattern_data.start.x;
    enemy->linear_fly_pattern_data.direction.y = enemy->linear_fly_pattern_data.end.y - enemy->linear_fly_pattern_data.start.y;
    enemy->linear_fly_pattern_data.distance = sqrtf(enemy->linear_fly_pattern_data.direction.x * enemy->linear_fly_pattern_data.direction.x + enemy->linear_fly_pattern_data.direction.y * enemy->linear_fly_pattern_data.direction.y);
    if (enemy->linear_fly_pattern_data.distance != 0) 
    {
      enemy->linear_fly_pattern_data.direction.x /= enemy->linear_fly_pattern_data.distance;
      enemy->linear_fly_pattern_data.direction.y /= enemy->linear_fly_pattern_data.distance;
    }
    enemy->center_pos.x += enemy->linear_fly_pattern_data.direction.x * enemy->linear_fly_pattern_data.speed * deltaTime;
    enemy->center_pos.y += enemy->linear_fly_pattern_data.direction.y * enemy->linear_fly_pattern_data.speed * deltaTime;

    float distance_traveled = sqrtf((enemy->center_pos.x - enemy->linear_fly_pattern_data.start.x) * (enemy->center_pos.x - enemy->linear_fly_pattern_data.start.x) + (enemy->center_pos.y - enemy->linear_fly_pattern_data.start.y) * (enemy->center_pos.y - enemy->linear_fly_pattern_data.start.y));
    
    if (distance_traveled >= enemy->linear_fly_pattern_data.distance) 
    {
      Vector2 temp = enemy->linear_fly_pattern_data.start;
      enemy->linear_fly_pattern_data.start = enemy->linear_fly_pattern_data.end;
      enemy->linear_fly_pattern_data.end = temp;
    }
  }
  else if( enemy->fly_pattern == CIRCULAR )
  {
    enemy->circular_fly_pattern_data.angle += enemy->circular_fly_pattern_data.angular_speed * deltaTime;
    enemy->center_pos.x = enemy->circular_fly_pattern_data.center.x + cosf(enemy->circular_fly_pattern_data.angle) * enemy->circular_fly_pattern_data.radius;
    enemy->center_pos.y = enemy->circular_fly_pattern_data.center.y + sinf(enemy->circular_fly_pattern_data.angle) * enemy->circular_fly_pattern_data.radius;
  }
  else if( enemy->fly_pattern == INFINITE )
  {
    //two circles, that touch in one point, and the enemy flies in the first and then the second and then the first and so on
  
    
  }
}
