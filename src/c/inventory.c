/*
Manages inventories (for both players and ennemies), including item creation, picking up, dropping, etc.
For entity management, see entity.c
For armor management, see armor.c
*/

#include "../headers/inventory.h"
#include "../headers/main.h"



struct Item create_item(struct ItemArray* items, int name, int type) {
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
    struct Item item = {.name = name, .type = type, .multiplier = multiplier, .durability = dura, .loaded = true, .is_in_inventory = false};
    printf("\ncreated item %d\n", name);
    add_item_array(items, &item);
    return (struct Item) item;
}

struct Inventory* init_slots() {
    struct Item slots[MAX_SLOTS] = {};
    struct Inventory* inv = malloc(sizeof(struct Inventory));
    if (inv == NULL) {
        perror("Out of Memory error: failed to allocate memory for inventory");
        exit(EXIT_FAILURE);
    }
    *inv->slots = *slots;
    inv->size = 0;
    inv->weapon = -1;
    inv->selected = -1;
    return (struct Inventory*) inv;
}

void pick_up(struct Inventory* inv, struct Item* item, int chapter) {
    if(!inv || !item) return;
    if(inv->size >= 5){
        drop_item(inv, &inv->slots[inv->selected], chapter);
    }
    item->is_in_inventory = true;
    inv->slots[inv->size] = *item;
    printf("player picked up item %d\n", item->name);
    inv->size++;
}

void drop_item(struct Inventory* inv, struct Item* item, int chapter) {
    if(!inv || !item) return;
    item->is_in_inventory = false;
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

void update_item_dura(struct ItemArray* items, struct Inventory* inv, int chapter) {
    if(!inv->weapon ) return;
    float *dura = &inv->slots[inv->weapon].durability;
    if(*dura == -1) return;
    *dura -= 5 * randomizer();
    if(*dura <= 0.0) {
        remove_item(items, inv, &inv->slots[inv->weapon], chapter);
        //playsound 
    }
}

void remove_item(struct ItemArray* items, struct Inventory* inv, struct Item* item, int chapter) {
    drop_item(inv, item, chapter);
    remove_item_array(items, item);
}

void free_inventory(struct ItemArray* items, struct Inventory* inv) {
    for (int i=0; i < inv->size; i++) {
        remove_item_array(items, &inv->slots[i]);
    }
}
