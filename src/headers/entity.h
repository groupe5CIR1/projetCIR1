#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "armor.h"
#include "inventory.h"

#define MAX_SLOTS 6

enum Type {
    PLAYER,
    MONSTER,
    ENNEMY,
};



struct Inventory {
    struct Item* slots[MAX_SLOTS];
    int size;
    bool weapon;
};

struct Entity {
    int uid;
    bool loaded;
    int type;
    float health;
    int defaultDamage;
    bool shield;
    struct Armor* armor;
    struct Inventory* inventory;
};


struct Entity init_entity(int type);

void damage(struct Entity* entity, struct Entity* entity2);

void death(struct Entities* entities, struct Entity* entity);

void fight(struct Entities* entities, struct Entity* Player, struct Entity* ennemy);


void equip_shield();

#endif