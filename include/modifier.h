#ifndef MODIFIER_H
#define MODIFIER_H


typedef struct
{
    float speed;
    float fire_rate;
    float radius;
}projectile_modifier;

typedef struct
{
    float speed;
}linear;

typedef struct
{
    float angular_speed;
    float radius;
}circular;

typedef struct
{
    float speed;
    float radius;
}infinite;

typedef struct
{
  projectile_modifier projectile;
  linear linear;
  circular circular;
  infinite infinite;

}EnemyModifiers;


void init_enemy_modifiers(EnemyModifiers enemy_modifiers[]);

#endif