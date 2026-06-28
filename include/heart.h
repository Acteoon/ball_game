#ifndef HEART_H
#define HEART_H

#include "raylib.h"
#include "constants.h"


typedef struct Health_bar 
{
    Texture2D *full_heart;
    Texture2D *empty_heart;
    int lives;
    int hearts;  
    float scale;
    int max_collums;
    float max_height;
    Vector2 start;
}Health_bar;

void Draw_health_bar(Health_bar health_bar);
Health_bar init_health_bar(Texture2D *full_heart, Texture2D *empty_heart);
#endif