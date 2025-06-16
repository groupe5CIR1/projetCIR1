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
    struct Item slots[MAX_SLOTS];
    int size;
    int weapon;
    int selected;
};




void pick_up(struct Inventory* inv, struct Item* item);

<<<<<<< HEAD
void drop_item(struct Item item);
=======
void drop_item(struct Inventory* inv, struct Item* item);
>>>>>>> 307416c565047cd7b8752d0c2863cfe3a816c0de

void update_item_dura(struct Inventory* inv);

#endif