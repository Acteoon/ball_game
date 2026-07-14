#ifndef MODIFIER_H
#define MODIFIER_H

typedef struct
{
    float add;
    float multiply;
}modifier;


//--------------ENEMY--------------
typedef struct
{
    modifier speed;
    modifier fire_rate;
    modifier radius;
}projectile_modifier;

typedef struct
{
    modifier speed;
}linear;

typedef struct
{
    modifier angular_speed;
    modifier radius;
}circular;

typedef struct
{
    modifier speed;
    modifier radius;
}infinite;

typedef struct
{
  projectile_modifier projectile;
  linear linear;
  circular circular;
  infinite infinite;

}EnemyModifiers;
//--------------ENEMY--------------

//--------------PLAYER--------------

typedef struct
{
    modifier scale; 
    modifier rotation; 
    modifier speed;
}PlayerModifiers;

//--------------PLAYER--------------

//--------------BALL--------------

typedef struct
{
    modifier speed;
    modifier radius;
    modifier max_speed;
    modifier min_speed;
}BallModifiers;

//--------------BALL--------------

//--------------GAME--------------


void init_enemy_modifiers(EnemyModifiers enemy_modifiers[]);
void init_player_modifiers(PlayerModifiers player_modifiers);
void init_ball_modifiers(BallModifiers ball_modifiers);

#endif