#include "raylib.h"
#include "constants.h"
#include "player.h"
#include "ball.h"
#include "enemy.h"
#include "modifier.h"
#include "projectile.h"

int main(void) 
{
  float deltaTime;
  int i;
  int lives = 3;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ball_Game");

  Texture2D player_texture = LoadTexture("assets/player.png");
  Texture2D enemy_normal_texture = LoadTexture("assets/enemy.png");
  Texture2D enemy_pest_texture = LoadTexture("assets/enemy.png");
  Texture2D enemy_buff_texture = LoadTexture("assets/enemy_evo.png");
  Texture2D ball_texture = LoadTexture("assets/ball.png");
  Texture2D projectile_texture = LoadTexture("assets/enemy_projectile.png");
  
  Player player;
  initialize_player(&player, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / PLAYER_SPAWN_DIVISOR, &player_texture);

  Ball ball;
  init_ball(&ball, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, &ball_texture);

  Texture2D enemy_textures[ENEMY_TYPE_COUNT] = {
    [NORMAL] = enemy_normal_texture,
    [PEST] = enemy_pest_texture,
    [BUFF] = enemy_buff_texture
  };

  Enemy enemy[ENEMY_COUNT] = {0};
  /*
  for (int i = 0; i < ENEMY_COUNT; i++)
  {
    fly_position pos = (fly_position)(i % 5);
    enemy_type type = (enemy_type)(i % 3);
    enemy_fly_pattern pattern = (enemy_fly_pattern)(i % 3);
    init_enemy(&enemy[i], pos, type, pattern, enemy_textures);
  } 
  */ 

  init_enemy(&enemy[0], CENTER, PEST, LINEAR, enemy_textures);
  init_enemy(&enemy[1], TOP_LEFT, PEST, CIRCULAR, enemy_textures);
  init_enemy(&enemy[2], TOP_RIGHT, NORMAL, INFINITE, enemy_textures);
  init_enemy(&enemy[3], CENTER, BUFF, CIRCULAR, enemy_textures);


  EnemyModifiers enemy_modifiers[3] = {
    [NORMAL] = {
      .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
      .linear = { .speed = 1.0f },
      .circular = { .angular_speed = 1.0f, .radius = 1.0f },
      .infinite = { .speed = 1.0f, .radius = 1.0f },
    },
    [PEST] = {
      .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
      .linear = { .speed = 1.0f },
      .circular = { .angular_speed = 1.0f, .radius = 1.0f },
      .infinite = { .speed = 1.0f, .radius = 1.0f },
    },
    [BUFF] = {
      .projectile = { .speed = 1.0f, .fire_rate = 1.0f, .radius = 1.0f },
      .linear = { .speed = 1.0f },
      .circular = { .angular_speed = 1.0f, .radius = 1.0f },
      .infinite = { .speed = 1.0f, .radius = 1.0f },
    }
  };

  Projectile projectiles[NUM_PROJECTILES];

  SetTargetFPS(FPS);

  while (!WindowShouldClose()) 
  {
    deltaTime = GetFrameTime();

    BeginDrawing();
    ClearBackground(SKYBLUE);

    update_player(&player, deltaTime);
    update_ball(&ball, &player, deltaTime);
    for (i = 0; i < ENEMY_COUNT; i++)
    {
      update_enemy(&enemy[i], deltaTime, &ball, enemy_modifiers, projectiles, &projectile_texture);
    }
    for ( i = 0; i < NUM_PROJECTILES; i++)
    {
       update_projectile(&projectiles[i], deltaTime, &player, &lives);
    }
    

    DrawTextureEx(player.texture, player.texture_pos, player.rotation, player.scale, WHITE);
    DrawTextureEx(ball.texture, ball.texture_pos, ball.rotation, ball.scale, WHITE);
    for (i = 0; i < ENEMY_COUNT; i++)
    {
      if (enemy[i].alive)
        DrawTextureEx(enemy[i].texture, enemy[i].texture_pos, enemy[i].rotation, enemy[i].scale, WHITE);
    }
    for ( i = 0; i < NUM_PROJECTILES; i++)
    {
      if(projectiles[i].active)
        DrawTextureEx(projectiles[i].texture, projectiles[i].texture_pos, projectiles[i].rotation, projectiles[i].scale, WHITE);
    }
    
    DrawRectangleLines(player.collision.x, player.collision.y, player.collision.width, player.collision.height, RED);
    DrawCircleLines(ball.texture_pos.x + ball.radius, ball.texture_pos.y + ball.radius, ball.radius, RED);
    EndDrawing();

    if (lives < 0)
      break;
  }
  UnloadTexture(player_texture);
  UnloadTexture(ball_texture);
  UnloadTexture(enemy_normal_texture);
  UnloadTexture(enemy_pest_texture);
  UnloadTexture(enemy_buff_texture);
  UnloadTexture(projectile_texture);


  CloseWindow();

  return 0;
}
