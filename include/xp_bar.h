#ifndef XP_BAR_H
#define XP_BAR_H

#include "raylib.h"
#include "constants.h"

typedef struct
{
    int percentage;
    float current_xp;
    float xp_to_next_level;
    int level;
    Vector2 center_pos;
    Vector2 texture_pos;
    Texture2D * empty_bar;
    Texture2D * bar_fluid;
    float scale;
    float rotation;
}Xp_bar;
 

void init_xp_bar(Xp_bar *xp_bar, Texture2D * bar_fluid, Texture2D * empty_bar);
void update_xp_bar(Xp_bar *xp_bar);
#endif