#ifndef ARMOR
#define ARMOR


#include <stdio.h>
#include <stdlib.h>

#include "entityArray.h"

struct Armor {
    char* name;
    int resistance;
    unsigned int durability;
};

void equip(struct Entity* player, struct Armor* armor);

void drop_armor(struct Entity* player, struct Armor* armor);

#endif