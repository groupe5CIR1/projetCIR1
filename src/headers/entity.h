#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "armor.h"
#include "inventory.h"
#include "entityArray.h"
#include "../headers/main.h"

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
    float defaultDamage;
    bool shield;
    struct Armor* armor;
    struct Inventory* inventory;
};


struct Entity* create_entity(struct Entities* entities, int type);

int get_new_uid(struct EntityArray* Arr);

void damage(struct ItemArray* items, struct Entity* attacker, struct Entity* defender);

void death(struct ItemArray* items, struct Entities* entities, struct Entity* entity);

void fight(struct ItemArray* items, struct Entities* entities, struct Entity* player, struct Entity* ennemy);


void equip_shield();

#endif