#include "raylib.h"
#include "player.h"
#include "ball.h"
#include "enemy.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(void) 
{
  const int screenWidth = SCREEN_WIDTH;
  const int screenHeight = SCREEN_HEIGHT;
  float deltaTime;
  
  InitWindow(screenWidth, screenHeight, "Ball_Game");
  
  Player player;
  initialize_player(&player, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 10);

  player.collision = (Rectangle){ .x = player.texture_pos.x, .y = player.texture_pos.y, .width = player.texture.width * player.scale, .height = player.texture.height * player.scale };

  Ball ball;
 
  init_ball(&ball, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  Enemy enemy[60];

  SetTargetFPS(60);

  while (!WindowShouldClose()) 
  {
    deltaTime = GetFrameTime();

    BeginDrawing();
    ClearBackground(SKYBLUE);

    update_player(&player, deltaTime);
    update_ball(&ball, &player, deltaTime);

    DrawTextureEx(player.texture, player.texture_pos, player.rotation, player.scale, WHITE);
    DrawTextureEx(ball.texture, ball.texture_pos, ball.rotation, ball.scale, WHITE);
    
    DrawRectangleLines(player.collision.x, player.collision.y, player.collision.width, player.collision.height, RED);
    DrawCircleLines(ball.texture_pos.x + ball.radius, ball.texture_pos.y + ball.radius, ball.radius, RED);
    EndDrawing();
  }
  UnloadTexture(player.texture);
  UnloadTexture(ball.texture);
  CloseWindow();

  return 0;
}
