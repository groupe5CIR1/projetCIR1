#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_SLOTS 6

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "itemArray.h"

enum ITEM {
    POTION,
    WEAPON,
};

enum NAME {
    ARME_INCROYABLE_SA_GRANMERE,
    DEUXIEME_ARME_INCROYABLE_SA_GRANMERE,
    ARME_INCASSABLE_C_EST_TROP_BI1_SAMERE,
};


struct Item {
    int name;
    int type;
    float multiplier;
    float durability;
    bool loaded;
    bool is_in_inventory;
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

void drop_item(struct Inventory* inv, struct Item* item, int chapter);

void update_item_dura(struct ItemArray* Arr, struct Inventory* inv, int chapter);

void remove_item(struct ItemArray* Arr, struct Inventory* inv, struct Item* item, int chapter);

void free_inventory(struct ItemArray* items, struct Inventory* inv);

#endif