#include "xp_bar.h"
#include "raylib.h"
#include "constants.h"

void init_xp_bar(Xp_bar *xp_bar, Texture2D * bar_fluid, Texture2D * empty_bar)
{
    xp_bar->center_pos.x = SCREEN_WIDTH / 2;
    xp_bar->center_pos.y = 30;
    xp_bar->bar_fluid = bar_fluid;
    xp_bar->empty_bar = empty_bar;
    xp_bar->scale = 6;
    xp_bar->texture_pos = (Vector2){ xp_bar->center_pos.x - (xp_bar->empty_bar->width * xp_bar->scale / 2), xp_bar->center_pos.y - (xp_bar->empty_bar->height * xp_bar->scale / 2) };
    xp_bar->rotation = 0;
    xp_bar->current_xp = 0.0f;
    xp_bar->level = 0;
    xp_bar->percentage = 0;
    xp_bar->xp_to_next_level = 10.0f;
}

void update_xp_bar(Xp_bar *xp_bar)
{
    //Update
    Rectangle bar_fluid_rect = { 0, 0, xp_bar->empty_bar->width * (xp_bar->percentage / 100.0f), xp_bar->empty_bar->height };
    
    //Draw
    DrawTextureEx(*xp_bar->empty_bar, xp_bar->texture_pos, xp_bar->rotation, xp_bar->scale, WHITE);
    DrawText(TextFormat("Level: %d", xp_bar->level), xp_bar->center_pos.x - 50, xp_bar->center_pos.y - 20, 20, BLACK);
    DrawTexturePro(*xp_bar->bar_fluid, bar_fluid_rect, (Rectangle){ xp_bar->texture_pos.x, xp_bar->texture_pos.y, bar_fluid_rect.width * xp_bar->scale, bar_fluid_rect.height * xp_bar->scale }, (Vector2){ 0, 0 }, xp_bar->rotation, WHITE);
}