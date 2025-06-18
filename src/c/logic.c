/*
Manages the main logic of the game.
Functions in this file are called whenever a page is refreshed, or whenever a button is clicked.
Note that the afomentionned button must have a tag indicating which action to execute.
In any case, the entities must be ticked, the game displayed and logic updated.

Note that html files are directly not modified here, see display.c for more information.
Note that this file does not manage the sockets that listen to the port 8080, see "main.c" for more information. 
*/

#include "../headers/logic.h"



bool btn_logic(struct Entities* entities, struct Entity* player, struct ItemArray* items, int chapter, int btn, int slot, int index_item) {
    if(btn == -1 || !chapter) return false;
    struct Inventory* inv = player->inventory;
    switch (btn) {
    case NEW_CHAPTER:
        load_page(entities, items, chapter);    //chapters à faire
        if (chapter == 1) {
            player_pickup(player, items, 0, chapter);
            printf("player picked up item : %d\n", player->inventory->slots[0]);
        }
        break;
    case FIGHT:
        fight_all(items, entities, player, chapter);
        break;
    case PICK_UP:
        player_pickup(player, items, index_item, chapter);     //modif le html pour avoir un btn par item à pickup
        break;
    case DROP:
        drop_item(inv, &inv->slots[inv->selected], chapter);
        break;
    case USE:
        player_use(player, items, chapter);
        break;
    case SLOT:
        inv->selected = slot;
        break;
    default:
        printf("Unknown button\n");
        break;
    }
    look_for_pickup();          //à faire
    update_inventory(inv, chapter);
    update_display(entities, player, items, chapter, btn, slot, index_item);           //Inutile, voir définition
    return true;
}

void load_page(struct Entities* entities, struct ItemArray* items, int chap) {
    for (int i=0; i < items->size; i++) {        //unload items
        if (!items->itemArray[i].is_in_inventory) {
            items->itemArray[i].loaded = false;
        }
    }
    for (int i=0; i < entities->loadedEntities->size; i++) {    //unload entities (except player)
        if (entities->loadedEntities->loaded_entities[i].type != PLAYER) {
            unload_entity(entities->loadedEntities, entities->loadedEntities->loaded_entities[i].uid);
        }
    }
    chapter(entities, items, chap);     //load entity & item chapters
}

void fight_all(struct ItemArray* items, struct Entities* entities, struct Entity* player, int chapter) {
    struct LoadedEntities* loaded_ntts = entities->loadedEntities;
    for(int i=0; i < loaded_ntts->size; i++) {
        if (loaded_ntts->loaded_entities[i].type != PLAYER)
            fight(items, entities, player, &loaded_ntts->loaded_entities[i], chapter);
    }
}

void player_pickup(struct Entity* player, struct ItemArray* items, int index_item, int chapter) {
    int loaded_item_counter = 0;
    for (int i=0; i < items->size; i++) {
        if (items->itemArray[i].loaded) {
            printf("loaded item : %d\n", items->itemArray[i].name);
            if (loaded_item_counter == index_item) {
                pick_up(player->inventory, &items->itemArray[i], chapter);
            }
            loaded_item_counter++;
        }
    }
}

void player_use(struct Entity* player, struct ItemArray* items, int chapter) {
    struct Item* selected_item = &player->inventory->slots[player->inventory->selected];
    if (selected_item->type == POTION) {
        player->health += 30;
    }
    remove_item(items, player->inventory, selected_item, chapter);
}


void look_for_pickup() {
    /*
    look for pickup items :
    - remove every item pickup button
    - find every loaded item (loaded tag)
    - create item pickup button for each loaded item
    */
}

//Inutile, les fonctions pour display (= modif le fichier) sont appelées à chaque fois qu'un changement est fait
void update_display(struct Entities* entities, struct Entity* player, struct ItemArray* items, int chapter, int btn, int slot, int item) {

}
