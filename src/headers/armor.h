#ifndef ARMOR_H
#define ARMOR_H


#include <stdio.h>
#include <stdlib.h>

#include "entity.h"


struct Armor {
    char* name;
    int resistance;
    float durability;
};

void equip(struct Entity* player, struct Armor* armor);

void drop_armor(struct Entity* player, struct Armor* armor);

void free_armor(struct Armor* armor);

#endif