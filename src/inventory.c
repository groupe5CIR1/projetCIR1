/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "inventory.h"


void pick_up(struct Inventory* inv) {

}


void drop_item(struct Inventory* inv) {

}

void update_item_dura(struct Inventory* inv) {
    if(!inv->weapon) return;
    float *dura = inv->inventory[inv->weapon].durability;
    *dura -= 5 * random();
    if(*dura <= 0.0) {
        break_item(inv->inventory[inv->weapon]);
    }
}



