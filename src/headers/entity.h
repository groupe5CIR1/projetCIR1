#ifndef ENTITY
#define ENTITY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "armor.h"
#include "inventory.h"
#include "entityArray.h"
#include "inventory.h"

#define MAX_SLOTS 6

enum Type {
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
    struct Inventory* inventory;
};


struct Entity* create_entity(struct Entities* Arr, int type);

int get_new_uid(struct Entities* entities);

void damage(struct Entity* entity, struct Entity* entity2);

void death(struct Entities* entities, struct Entity* entity);

void fight(struct ItemArray* items, struct Entities* entities, struct Entity* Player, struct Entity* ennemy);


void equip_shield();

#endif