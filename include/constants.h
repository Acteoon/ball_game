#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
#include "enemy.h"

#define SCREEN_WIDTH   1920
#define SCREEN_HEIGHT  1080
#define FPS            60
#define ENEMY_COUNT    60

#define BASE_HEALTH 3
#define HEARTS_BASE_SCALE 4.0f
#define HEARTS_BASE_MAX_COLLUMS 10
#define HEARTS_BASE_MAX_HEIGHT 200.0f

#define TWO_PI  6.28318530718f

#define PLAYER_SCALE          7.0f
#define PLAYER_SPAWN_DIVISOR  10

#define BALL_SCALE              4.0f
#define BALL_INITIAL_SPEED_X    0
#define BALL_INITIAL_SPEED_Y    -800
#define BALL_BOUNCE_MULTIPLIER  1.0f
#define BALL_PADDLE_SPEED_MULTIPLIER  1.5f

#define GRAVITY    7
#define MAX_SPEED  1000

#define ENEMY_SCALE_NORMAL  6.0f
#define ENEMY_SCALE_PEST    4.0f
#define ENEMY_SCALE_BUFF    7.0f
#define ENEMY_FIRERATE_NORMAL 10.0f
#define ENEMY_FIRERATE_PEST 5.0f
#define ENEMY_FIRERATE_BUFF 15.0f
#define ENEMY_PROJECTILE_SPEED_NORMAL 100
#define ENEMY_PROJECTILE_SPEED_PEST 200
#define ENEMY_PROJECTILE_SPEED_BUFF 100
#define ENEMY_PROJECTILE_SCALE_NORMAL 3.0f
#define ENEMY_PROJECTILE_SCALE_PEST 3.0f
#define ENEMY_PROJECTILE_SCALE_BUFF 3.0f

#define ENEMY_SPAWN_TIME_MIN 600
#define ENEMY_SPAWN_TIME_MAX 800

#define NUM_PROJECTILES 100

static const Vector2 TOP_LEFT_SPAWN     = { 100.0f, 100.0f };
static const Vector2 TOP_RIGHT_SPAWN    = { (float)(SCREEN_WIDTH - 100), 100.0f };
static const Vector2 BOTTOM_LEFT_SPAWN  = { 100.0f, (float)(SCREEN_HEIGHT/2) };
static const Vector2 BOTTOM_RIGHT_SPAWN = { (float)(SCREEN_WIDTH - 100), (float)(SCREEN_HEIGHT/2) };
static const Vector2 CENTER_SPAWN       = { (float)(SCREEN_WIDTH/2), (float)(SCREEN_HEIGHT/4) };

static const EnemyConfig ENEMY_CONFIGS[ENEMY_TYPE_COUNT] = {
  [NORMAL] = {
    .linear   = { .speed = 100.0f, .distance = 200.0f, .angle = 0.0f },
    .circular = { .radius = 50.0f, .angular_speed = 1.0f },
    .infinite = { .radius = 50.0f, .speed = 1.0f },
  },
  [PEST] = {
    .linear   = { .speed = 150.0f, .distance = 150.0f, .angle = 0.0f },
    .circular = { .radius = 70.0f, .angular_speed = 1.5f },
    .infinite = { .radius = 70.0f, .speed = 2.0f },
  },
  [BUFF] = {
    .linear   = { .speed = 80.0f,  .distance = 50.0f,  .angle = 0.0f },
    .circular = { .radius = 30.0f, .angular_speed = 0.5f },
    .infinite = { .radius = 30.0f, .speed = 0.7f },
  },
};

#endif