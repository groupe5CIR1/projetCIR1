#ifndef INVENTORY
#define INVENTORY

#define MAX_SLOTS 6

#include <stdio.h>
#include <stdlib.h>

enum ITEM {
    POTION,
    WEAPON
};

enum NAME {
    ARME_INCROYABLE_SA_GRANMERE,
    DEUXIEME_ARME_INCROYABLE_SA_GRANMERE,
    ARME_INCASSABLE_C_EST_TROP_BI1_SAMERE
};


struct Item {
    int name;
    int type;
    float multiplier;
    float durability;
};

struct Inventory {
    struct Item slots[MAX_SLOTS];   
    int size;
    int weapon;
    int selected;
};



struct Item create_item(struct ItemArray* Arr, int name, int type);

struct Inventory* init_slots();

void pick_up(struct Inventory* inv, struct Item* item);

void drop_item(struct Inventory* inv, struct Item* item);

void update_item_dura(struct ItemArray* Arr, struct Inventory* inv);

void remove_item(struct ItemArray* Arr, struct Inventory* inv, struct Item* item);

#endif