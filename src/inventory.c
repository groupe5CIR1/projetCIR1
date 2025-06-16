/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "inventory.h"


void pick_up(struct Inventory* inv, struct Item* item) {

}


void drop_item(struct Inventory* inv, struct Item* item) {

}

void update_item_dura(struct Inventory* inv) {
    if(!inv->weapon) return;
<<<<<<< HEAD
    inv->slots[inv->weapon].durability *= random();
=======
    float *dura = inv->inventory[inv->weapon].durability;
    *dura -= 5 * random();
    if(*dura <= 0.0) {
        break_item(inv->inventory[inv->weapon]);
    }
>>>>>>> 307416c565047cd7b8752d0c2863cfe3a816c0de
}



