#include "player.h"

void update_player(Player *player, float deltaTime)
{
  Vector2 mouse = GetMousePosition();

  player->center_pos.x = mouse.x;
  player->texture_pos.x = player->center_pos.x - (player->texture.width * player->scale / 2);
  player->collision.x = player->center_pos.x - (player->texture.width * player->scale / 2);
}
