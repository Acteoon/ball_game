#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "heart.h"

typedef struct Player Player;

typedef struct Ball
{
  Texture texture;
  Vector2 texture_pos;
  Vector2 center_pos;
  float radius;
  float scale;
  float rotation;
  Vector2 speed;
} Ball;

void init_ball(Ball *ball, float x, float y, Texture2D *texture);
void update_ball(Ball *ball, Player *player, float deltaTime, Health_bar *health_bar);

#endif
