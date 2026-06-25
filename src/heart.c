#include "heart.h"
#include "raylib.h"
#include "stdlib.h"
#include "math.h"

void Draw_health_bar(Health_bar health_bar)
{
    float start_x = health_bar.start.x;
    float start_y = health_bar.start.y;
    float heart_w = (float)health_bar.full_heart->width;
    float heart_h = (float)health_bar.full_heart->height;
    float bar_width = health_bar.max_collums * heart_w * health_bar.scale;

    int cols = health_bar.max_collums;
    float scale = health_bar.scale;

    while (cols < health_bar.hearts)
    {
        int rows = (health_bar.hearts + cols - 1) / cols;
        float total_height = rows * heart_h * scale;
        if (total_height <= health_bar.max_height)
            break;
        cols++;
        scale = fminf(health_bar.scale, bar_width / (cols * heart_w));
    }

    int rows = (health_bar.hearts + cols - 1) / cols;
    float total_height = rows * heart_h * scale;
    if (total_height > health_bar.max_height)
        scale *= health_bar.max_height / total_height;

    float draw_w = heart_w * scale;
    float draw_h = heart_h * scale;

    for (int i = 0; i < health_bar.hearts; i++)
    {
        int row = i / cols;
        int col = i % cols;
        Vector2 pos = {
            start_x + col * draw_w,
            start_y + row * draw_h
        };
        Texture2D *tex = (i < health_bar.lives) ? health_bar.full_heart : health_bar.empty_heart;
        DrawTextureEx(*tex, pos, 0.0f, scale, WHITE);
    }
}