#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "armor.h"
#include "inventory.h"

#define MAX_SLOTS 6

enum Type{
    PLAYER,
    MONSTER,
    ENNEMY,
};

struct Entity {
    int uid;
    bool loaded;
    int type;
    float health;
    int defaultDamage;
    bool shield;
    struct Armor* armor;
    struct Item* inventory;
};


struct Entity init_entity(int type);

void damage(struct Entity* entity, struct Entity* entity2);

void equip_shield();

#endif