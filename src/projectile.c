#include "projectile.h"
#include "player.h"
#include "enemy.h"
#include "constants.h"
#include <math.h>

void update_projectile(Projectile *projectile, float deltaTime, Player *player, int *lives)
{
  if (!projectile->active)
    return;

  if (projectile->active && CheckCollisionRecs(projectile->collision, player->collision))
  {
    projectile->active = false;
  }

  projectile->collision = (Rectangle){.x = projectile->center_pos.x, .y = projectile->center_pos.y, .width = projectile->texture.width * projectile->scale, .height = projectile->texture.height * projectile->scale };
  projectile->center_pos.x += projectile->direction.x * projectile->speed * deltaTime;
  projectile->center_pos.y += projectile->direction.y * projectile->speed * deltaTime;

  if (projectile->center_pos.x - projectile->collision.width * 0.5f < 0 || projectile->center_pos.x + projectile->collision.width * 0.5f >= SCREEN_WIDTH)
  {
    projectile->direction.x = -projectile->direction.x;
  }

  if (projectile->center_pos.y - projectile->collision.height * 0.5f < 0)
  {
    projectile->direction.y = -projectile->direction.y;
  }

  if (projectile->center_pos.y + (projectile->collision.height * 0.5f) >= SCREEN_HEIGHT)
  {
    (*lives)--;
    projectile->active = false;
  }

  projectile->texture_pos = (Vector2){ projectile->center_pos.x - (projectile->texture.width * projectile->scale * 0.5f), projectile->center_pos.y - (projectile->texture.height * projectile->scale * 0.5f) };
}



void init_projectile(Projectile *projectile, Enemy *enemy, Texture2D *texture)
{
  projectile->texture = *texture;
  projectile->center_pos = enemy->center_pos;
  projectile->direction = enemy->projectile.direction;
  projectile->speed = enemy->projectile.speed;
  projectile->collision = (Rectangle){.x = projectile->center_pos.x, .y = projectile->center_pos.y, .width = projectile->texture.width * projectile->scale, .height = projectile->texture.height * projectile->scale };
  projectile->active = true;
  projectile->scale = enemy->projectile.scale;
  projectile->rotation = 0.0f;
  projectile->texture_pos = (Vector2){ projectile->center_pos.x - (projectile->texture.width * projectile->scale * 0.5f), projectile->center_pos.y - (projectile->texture.height * projectile->scale * 0.5f) };
}