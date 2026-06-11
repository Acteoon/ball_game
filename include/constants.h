#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

#define SCREEN_WIDTH   1920
#define SCREEN_HEIGHT  1080
#define FPS            60
#define ENEMY_COUNT    60

//player constants
#define PLAYER_SCALE          7.0f
#define PLAYER_SPAWN_DIVISOR  10

//ball constants
#define BALL_SCALE              4.0f
#define BALL_INITIAL_SPEED_X    350
#define BALL_BOUNCE_MULTIPLIER  1.1f

//enemy constants
#define TWO_PI  6.28318530718f
#define ENEMY_SCALE             3.0f

#define ENEMY_LINEAR_SPEED_NORMAL   100.0f
#define ENEMY_LINEAR_SPEED_PEST     150.0f
#define ENEMY_LINEAR_SPEED_BUFF      80.0f

#define ENEMY_CIRCULAR_RADIUS_NORMAL     50.0f
#define ENEMY_CIRCULAR_RADIUS_PEST       70.0f
#define ENEMY_CIRCULAR_RADIUS_BUFF       30.0f
#define ENEMY_CIRCULAR_SPEED_NORMAL       1.0f
#define ENEMY_CIRCULAR_SPEED_PEST         1.5f
#define ENEMY_CIRCULAR_SPEED_BUFF         0.5f

#define ENEMY_INFINITE_RADIUS_NORMAL     50.0f
#define ENEMY_INFINITE_RADIUS_PEST       70.0f
#define ENEMY_INFINITE_RADIUS_BUFF       30.0f
#define ENEMY_INFINITE_SPEED_NORMAL       1.0f
#define ENEMY_INFINITE_SPEED_PEST         1.5f
#define ENEMY_INFINITE_SPEED_BUFF         0.5f

static const Vector2 TOP_LEFT_SPAWN     = { 100.0f, 100.0f };
static const Vector2 TOP_RIGHT_SPAWN    = { (float)(SCREEN_WIDTH - 100), 100.0f };
static const Vector2 BOTTOM_LEFT_SPAWN  = { 100.0f, (float)(SCREEN_HEIGHT/2) };
static const Vector2 BOTTOM_RIGHT_SPAWN = { (float)(SCREEN_WIDTH - 100), (float)(SCREEN_HEIGHT/2) };
static const Vector2 CENTER_SPAWN       = { (float)(SCREEN_WIDTH/2), (float)(SCREEN_HEIGHT/4) };

//physics constants
#define GRAVITY    15
#define MAX_SPEED  500

#endif
