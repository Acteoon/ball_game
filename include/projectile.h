#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Player Player;
typedef struct Enemy Enemy;

typedef struct Projectile
{
  Texture2D texture;
  Vector2 center_pos;
  Vector2 texture_pos;
  Vector2 direction;
  Rectangle collision;
  float rotation;
  float scale;
  float speed;
  bool active;
}Projectile;

void update_projectile(Projectile *projectile, float deltaTime, Player *player, int *lives);
void init_projectile(Projectile *projectile, Enemy *enemy, Texture2D *texture);



#endif
