#include "player.h"
#include "constants.h"


void initialize_player(Player *player, float x, float y, Texture2D *texture)
{
  player->texture = *texture;
  player->center_pos = (Vector2){ .x = x, .y = y };
  player->scale = PLAYER_SCALE;
  player->texture_pos = (Vector2){ player->center_pos.x - (player->texture.width * player->scale / 2), player->center_pos.y - (player->texture.height * player->scale / 2) };
  player->rotation = 0.0f;
  player->speed = (Vector2){ .x = 0, .y = 0 };
  player->collision = (Rectangle){ .x = player->texture_pos.x, .y = player->texture_pos.y, .width = player->texture.width * player->scale, .height = player->texture.height * player->scale };
}
void update_player(Player *player, float deltaTime)
{
  Vector2 mouse = GetMousePosition();

  player->center_pos.x = mouse.x;
  player->texture_pos.x = player->center_pos.x - (player->texture.width * player->scale / 2);
  player->collision.x = player->center_pos.x - (player->texture.width * player->scale / 2);
}
