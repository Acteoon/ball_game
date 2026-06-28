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
    xp_bar->current_xp = 0;
    xp_bar->level = 0;
    xp_bar->percentage = 0;
    xp_bar->xp_to_next_level = 10;

    
}

void draw_xp_bar(Xp_bar *xp_bar)
{
    DrawTextureEx(*xp_bar->empty_bar, xp_bar->texture_pos, xp_bar->rotation, xp_bar->scale, WHITE);
}