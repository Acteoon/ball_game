#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
#include "enemy.h"

#define SCREEN_WIDTH   1920
#define SCREEN_HEIGHT  1080
#define FPS            60
#define ENEMY_COUNT    60

#define TWO_PI  6.28318530718f

#define PLAYER_SCALE          7.0f
#define PLAYER_SPAWN_DIVISOR  10

#define BALL_SCALE              4.0f
#define BALL_INITIAL_SPEED_X    350
#define BALL_BOUNCE_MULTIPLIER  1.1f

#define ENEMY_SCALE  3.0f

#define GRAVITY    15
#define MAX_SPEED  500

static const Vector2 TOP_LEFT_SPAWN     = { 100.0f, 100.0f };
static const Vector2 TOP_RIGHT_SPAWN    = { (float)(SCREEN_WIDTH - 100), 100.0f };
static const Vector2 BOTTOM_LEFT_SPAWN  = { 100.0f, (float)(SCREEN_HEIGHT/2) };
static const Vector2 BOTTOM_RIGHT_SPAWN = { (float)(SCREEN_WIDTH - 100), (float)(SCREEN_HEIGHT/2) };
static const Vector2 CENTER_SPAWN       = { (float)(SCREEN_WIDTH/2), (float)(SCREEN_HEIGHT/4) };

static const EnemyConfig ENEMY_CONFIGS[ENEMY_TYPE_COUNT] = {
  [NORMAL] = {
    .linear   = { .speed = 100.0f, .distance = 100.0f, .angle = 0.0f },
    .circular = { .radius = 50.0f, .angular_speed = 1.0f },
    .infinite = { .radius = 50.0f, .speed = 1.0f },
  },
  [PEST] = {
    .linear   = { .speed = 150.0f, .distance = 150.0f, .angle = 0.0f },
    .circular = { .radius = 70.0f, .angular_speed = 1.5f },
    .infinite = { .radius = 70.0f, .speed = 1.5f },
  },
  [BUFF] = {
    .linear   = { .speed = 80.0f,  .distance = 50.0f,  .angle = 0.0f },
    .circular = { .radius = 30.0f, .angular_speed = 0.5f },
    .infinite = { .radius = 30.0f, .speed = 0.5f },
  },
};

#endif