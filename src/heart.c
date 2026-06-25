#include "heart.h"
#include "raylib.h"
#include "stdlib.h"

void Draw_health_bar(Health_bar health_bar)
{
    float start_x = health_bar.start.x;
    float start_y = health_bar.start.y;

    int rows = (health_bar.hearts + health_bar.max_collums - 1) / health_bar.max_collums;
    float heart_width = health_bar.full_heart->width * health_bar.scale;
    float heart_height = health_bar.full_heart->height * health_bar.scale;
    float total_height = rows * heart_height;

    float final_scale = health_bar.scale;
    if (total_height > health_bar.max_height)
        final_scale *= health_bar.max_height / total_height;

    heart_width = health_bar.full_heart->width * final_scale;
    heart_height = health_bar.full_heart->height * final_scale;

    for (int i = 0; i < health_bar.hearts; i++)
    {
        int row = i / health_bar.max_collums;
        int col = i % health_bar.max_collums;
        Vector2 pos = {
            start_x + col * heart_width,
            start_y + row * heart_height
        };
        Texture2D *tex = (i < health_bar.lives) ? health_bar.full_heart : health_bar.empty_heart;
        DrawTextureEx(*tex, pos, 0.0f, final_scale, WHITE);
    }
}