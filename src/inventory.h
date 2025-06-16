#ifndef INVENTORY
#define INVENTORY

#define MAX_SLOTS 6

#include <stdio.h>
#include <stdlib.h>

enum ITEM{
    potion,
    weapon
};

enum NAME {
    ARME_INCROYABLE_SA_GRANMERE,
    DEUXIEME_ARME_INCROYABLE_SA_GRANMERE
};


struct Item {
    int name;
    int type;
    float multiplier;
    unsigned int durability;
};

struct Inventory {
    struct Item inventory[MAX_SLOTS];
    int size;
    int weapon;
};




void pick_up(struct Inventory* inv, struct Item item);

void drop_item(struct Inventory* inv, struct Item item);

void update_item_dura(struct Inventory* inv);

#endif