/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "inventory.h"


void pick_up(struct Inventory* inv, struct Item item) {

}


void drop_item(struct Inventory* inv, struct Item item) {

}

void update_item_dura(struct Inventory* inv) {
    if(!inv->weapon) return;
    inv->inventory[inv->weapon].durability *= random();
}
