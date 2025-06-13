#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "armor.h"
#include "inventory.h"

#define MAX_SLOTS 5


struct Entity {
    int uid;
    char* type;
    unsigned int health;
    int defaultDamage;
    bool shield;
    struct Armor* armor;
    struct Item* inventory;
};

struct Entity* init_entity(char* entity);

void damage(struct Entity* player, struct Entity* entity);

void equip_shield();

#endif