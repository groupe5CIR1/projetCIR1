#ifndef INVENTORY
#define INVENTORY

#define MAX_SLOTS 6

#include <stdio.h>
#include <stdlib.h>

struct Item {
    int name;
    int type;
    float multiplier;
    unsigned int durability;
};

struct Inventory{
    struct Item* inventory[MAX_SLOTS];
    int size;
    int weapon;
};

/* 
enum ITEM{
potion
weapon
}



enume Name{
arme_incroyable_sagranmer
deuxieme_arme_incroyable_sa_granmer
}
*/



void pick_up(struct Entity* player, struct Item item);

void drop_item(struct Entity* entity, struct Item item);

#endif