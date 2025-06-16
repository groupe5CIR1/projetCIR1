/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "../headers/inventory.h"
#include "../headers/itemArray.h"



struct Item create_item(struct ItemArray* Arr, int name, int type) {
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
    struct Item item = {.name = name, .type = type, .multiplier = multiplier, .durability = dura};
    add_item_array(Arr, &item);
    return (struct Item) item;
}

struct Inventory* init_slots() {
    struct Item slots[MAX_SLOTS];
    for(int i=0; i < MAX_SLOTS; i++) {
        slots[i] = (struct Item){NULL};
    }
    struct Inventory inv = {.slots = slots, .size = -1, .weapon = -1, .selected = -1};
    return (struct Inventory*) &inv;
}

void pick_up(struct Inventory* inv, struct Item* item) {
    if(!inv || !item) return;
    if(inv->size >= 6){
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

void update_item_dura(struct ItemArray* Arr, struct Inventory* inv) {
    if(!inv->weapon ) return;
    float *dura = &inv->slots[inv->weapon].durability;
    if(*dura == -1) return;
    *dura -= 5 * random();
    if(*dura <= 0.0) {
        remove_item(Arr, inv, &inv->slots[inv->weapon]);
        //playsound 
    }
}

void remove_item(struct ItemArray* Arr, struct Inventory* inv, struct Item* item) {
    drop_item(inv, item);
    remove_item_array(Arr, item);
}

