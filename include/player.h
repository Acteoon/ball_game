#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player 
{
  Texture texture;
  Vector2 center_pos;
  Vector2 texture_pos;
  float scale;
  float rotation;
  Vector2 speed;
  Rectangle collision;
} Player;

void update_player(Player *player, float deltaTime);

#endif
