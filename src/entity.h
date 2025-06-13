#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "armor.h"
#include "inventory.h"

#define MAX_SLOTS 6


struct Entity {
    int uid;
    bool loaded;
    char* type;
    unsigned int health;
    int defaultDamage;
    bool shield;
    struct Armor* armor;
    struct Item* inventory;
};

struct Entity* init_entity(char* entity);

void damage(struct Entity* entity, struct Entity* entity2);

void equip_shield();

#endif