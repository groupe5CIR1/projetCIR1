/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "inventory.h"



struct Item create_item(int name, int type) {
    float dura, multiplier;
    if(type == WEAPON) {
        switch (name) {
        case ARME_INCROYABLE_SA_GRANMERE:
            multiplier = 2;
            dura = 30;
            break;
        case DEUXIEME_ARME_INCROYABLE_SA_GRANMERE:
            multiplier = 5;
            dura = 40;
            break;
        case ARME_INCASSABLE_C_EST_TROP_BI1_SAMERE:
            multiplier = 8;
            dura = -1;
            break;
        default:
            multiplier = 1;
            dura = 20;
            break;
        }
    }
    return (struct Item) {.name = name, .type = type, .multiplier = multiplier, .durability = dura};
}


void pick_up(struct Inventory* inv, struct Item* item) {
    if(!inv || !item) return;
    if(inv->size >= 6 ){
        //demander de drop un item
    }
    inv->slots[inv->size] = *item;
    return;
}


void drop_item(struct Inventory* inv, struct Item* item) {
    if(!inv || !item) return;
    for(int i=0; i< inv->size; i++){
        if(&inv->slots[i] == item){
            for(int j=i; i < inv->size; j++){
                inv->slots[j]=inv->slots[j+1];
            }
            inv->size--;
            if (inv->weapon == i) inv->weapon = -1;
            else if (inv->weapon > i) inv->weapon--;

            if (inv->selected == i) inv->selected = -1;
            else if (inv->selected > i) inv->selected--;
        }

    }
}

void update_item_dura(struct Inventory* inv) {
    if(!inv->weapon ) return;
    float *dura = &inv->slots[inv->weapon].durability;
    if(*dura == -1) return;
    *dura -= 5 * random();
    if(*dura <= 0.0) {
        remove_item(inv, &inv->slots[inv->weapon]);
        //playsound 
    }
}



