#ifndef INVENTORY
#define INVENTORY

#include <stdio.h>
#include <stdlib.h>

struct Item {
    char* name;
    float multiplier;
    unsigned int durability;
};

void pick_up(struct Entity* player, struct Item item);

void drop_item(struct Entity* entity, struct Item item);

#endif