#include "comon.h"

int main(void) 
{
  float deltaTime;
  int i;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ball_Game");

  Texture2D player_texture = LoadTexture("assets/player.png");
  Texture2D enemy_normal_texture = LoadTexture("assets/enemy.png");
  Texture2D enemy_pest_texture = LoadTexture("assets/enemy_pest.png");
  Texture2D enemy_buff_texture = LoadTexture("assets/enemy_evo.png");
  Texture2D ball_texture = LoadTexture("assets/ball.png");
  Texture2D projectile_texture = LoadTexture("assets/enemy_projectile.png");
  Texture2D full_heart = LoadTexture("assets/full_heart.png");
  Texture2D empty_heart = LoadTexture("assets/empty_heart.png");
  Texture2D empty_bar = LoadTexture("assets/xp_bar_empty.png");
  Texture2D bar_fluid = LoadTexture("assets/xp_bar_insides.png");

  Upgrades upgrades = {
    .player_move_with_mouse = false,
    .player_kill_enemy_on_collision = false,
    .ball_kill_projectiles = false,
    .heart_on_ball_touch_ground = true,
    .ball_dublicate_on_enemy = { .active = false, .chance_percentage = 0 },
    .ball_homming = { .active = false, .quantity = 0 }
  };
  
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

  EnemyModifiers enemy_modifiers[ENEMY_TYPE_COUNT];
  init_enemy_modifiers(enemy_modifiers);

  Health_bar health_bar = init_health_bar(&full_heart, &empty_heart);

  Projectile projectiles[NUM_PROJECTILES];
  Enemy_spawner enemy_spawner = {.time = 0, .time_for_next_spawn = 0};
  Xp_bar xp_bar; init_xp_bar(&xp_bar, &bar_fluid, &empty_bar);

  SetTargetFPS(FPS);
  //SetMousePosition(player.center_pos.x, player.center_pos.y);
  HideCursor();

  while (!WindowShouldClose()) 
  {
    deltaTime = GetFrameTime();
    SetRandomSeed((int)(GetTime() * 3));
    spawn_enemys(enemy, &enemy_spawner, enemy_textures);
    BeginDrawing();
    ClearBackground(SKYBLUE);
    
    update_player(&player, deltaTime);
    update_ball(&ball, &player, deltaTime, &health_bar, &upgrades);
    for (i = 0; i < ENEMY_COUNT; i++)
    {
      update_enemy(&enemy[i], deltaTime, &ball, enemy_modifiers, projectiles, &projectile_texture);
    }
    for ( i = 0; i < NUM_PROJECTILES; i++)
    {
       update_projectile(&projectiles[i], deltaTime, &player, &health_bar);
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

    Draw_health_bar(health_bar);
    update_xp_bar(&xp_bar);
    
    //debugging
    //DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, BLACK);
    //DrawRectangleLines(player.collision.x, player.collision.y, player.collision.width, player.collision.height, RED);
    //DrawCircleLines(ball.texture_pos.x + ball.radius, ball.texture_pos.y + ball.radius, ball.radius, RED);
    
    EndDrawing();
    if (health_bar.lives <= 0)
      break;
  }

  
  UnloadTexture(player_texture);
  UnloadTexture(ball_texture);
  UnloadTexture(enemy_normal_texture);
  UnloadTexture(enemy_pest_texture);
  UnloadTexture(enemy_buff_texture);
  UnloadTexture(projectile_texture);
  UnloadTexture(full_heart);
  UnloadTexture(empty_heart);
  UnloadTexture(bar_fluid);
  UnloadTexture(empty_bar);

  CloseWindow();

  return 0;
}
