#include "raylib.h"
#include "constants.h"
#include "player.h"
#include "ball.h"
#include "enemy.h"

int main(void) 
{
  const int screenWidth = SCREEN_WIDTH;
  const int screenHeight = SCREEN_HEIGHT;
  float deltaTime;
  
  InitWindow(screenWidth, screenHeight, "Ball_Game");
  
  Player player;
  initialize_player(&player, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / PLAYER_SPAWN_DIVISOR);

  Ball ball;
 
  init_ball(&ball, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  Enemy enemy[ENEMY_COUNT] = {0};
  /*
  for (int i = 0; i < ENEMY_COUNT; i++)
  {
    fly_position pos = (fly_position)(i % 5);
    enemy_type type = (enemy_type)(i % 3);
    enemy_fly_pattern pattern = (enemy_fly_pattern)(i % 3);
    init_enemy(&enemy[i], pos, type, pattern);
  } 
  */ 

  init_enemy(&enemy[0], CENTER, PEST, LINEAR);
  init_enemy(&enemy[1], TOP_LEFT, PEST, CIRCULAR);
  init_enemy(&enemy[2], TOP_RIGHT, NORMAL, INFINITE);
  init_enemy(&enemy[3], CENTER, BUFF, CIRCULAR);


  SetTargetFPS(FPS);

  while (!WindowShouldClose()) 
  {
    deltaTime = GetFrameTime();

    BeginDrawing();
    ClearBackground(SKYBLUE);

    update_player(&player, deltaTime);
    update_ball(&ball, &player, deltaTime);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
      update_enemy(&enemy[i], deltaTime, &ball);
    }

    DrawTextureEx(player.texture, player.texture_pos, player.rotation, player.scale, WHITE);
    DrawTextureEx(ball.texture, ball.texture_pos, ball.rotation, ball.scale, WHITE);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
      if (enemy[i].alive)
        DrawTextureEx(enemy[i].texture, enemy[i].texture_pos, enemy[i].rotation, enemy[i].scale, WHITE);
    }
    
    DrawRectangleLines(player.collision.x, player.collision.y, player.collision.width, player.collision.height, RED);
    DrawCircleLines(ball.texture_pos.x + ball.radius, ball.texture_pos.y + ball.radius, ball.radius, RED);
    EndDrawing();
  }
  UnloadTexture(player.texture);
  UnloadTexture(ball.texture);
  for (int i = 0; i < ENEMY_COUNT; i++) 
  {
    if (enemy[i].alive)
      UnloadTexture(enemy[i].texture);
  }
  CloseWindow();

  return 0;
}
