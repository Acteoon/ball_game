#include "ball.h"
#include "player.h"
#include "constants.h"

void init_ball(Ball *ball, float x, float y, Texture2D *texture)
{
  ball->texture = *texture;
  ball->center_pos = (Vector2){ .x = x, .y = y };
  ball->scale = BALL_SCALE;
  ball->texture_pos = (Vector2){ ball->center_pos.x - (ball->texture.width * ball->scale / 2), ball->center_pos.y - (ball->texture.height * ball->scale / 2) };
  ball->rotation = 0.0f;
  ball->speed = (Vector2){ .x = BALL_INITIAL_SPEED_X, .y = BALL_INITIAL_SPEED_Y };
  ball->radius = ball->texture.width * ball->scale / 2;
}

void update_ball(Ball *ball, Player *player, float deltaTime)
{
  if (ball->center_pos.y + ball->radius >= SCREEN_HEIGHT) 
  {
    ball->center_pos.y = SCREEN_HEIGHT - ball->radius;
    ball->speed.y *= -BALL_BOUNCE_MULTIPLIER;
  }
  if (ball->center_pos.x + ball->radius >= SCREEN_WIDTH) 
  {
    ball->center_pos.x = SCREEN_WIDTH - ball->radius;
    ball->speed.x *= -BALL_BOUNCE_MULTIPLIER;
  }
  if (ball->center_pos.x - ball->radius <= 0) 
  {
    ball->center_pos.x = ball->radius;
    ball->speed.x *= -BALL_BOUNCE_MULTIPLIER;
  }
  if (ball->center_pos.y - ball->radius <= 0) 
  {
    ball->center_pos.y = ball->radius;
    ball->speed.y *= -BALL_BOUNCE_MULTIPLIER;
  }

  if (CheckCollisionCircleRec(ball->center_pos, ball->radius, player->collision)) 
  {
    ball->center_pos.y = player->collision.y - ball->radius;
    ball->speed.y *= -BALL_BOUNCE_MULTIPLIER;
    ball->speed.x += (ball->center_pos.x - player->center_pos.x) * BALL_PADDLE_SPEED_MULTIPLIER;
  }

  //ball->speed.y += GRAVITY;
  
  if (ball->speed.x  > MAX_SPEED) ball->speed.x = MAX_SPEED ;
  if (ball->speed.x  < -MAX_SPEED) ball->speed.x = -MAX_SPEED; 
  if (ball->speed.y  > MAX_SPEED) ball->speed.y = MAX_SPEED ;
  if (ball->speed.y  < -MAX_SPEED) ball->speed.y = -MAX_SPEED ;

  ball->center_pos.x += ball->speed.x * deltaTime;
  ball->center_pos.y += ball->speed.y * deltaTime;
  
  ball->texture_pos.x = ball->center_pos.x - (ball->texture.width * ball->scale / 2);
  ball->texture_pos.y = ball->center_pos.y - (ball->texture.height * ball->scale / 2);
}
