#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../headers/entityArray.h"
#include "../headers/entity.h"
#include "../headers/itemArray.h"
#include "../headers/inventory.h"
#include "../headers/display.h"
#include "../headers/chapters.h"


enum BUTTON {
    NEW_CHAPTER,
    FIGHT,
    PICK_UP,
    DROP,
    USE,
    SLOT
};


float btn_logic(struct Entities* entities, struct Entity* player, struct ItemArray* items, bool new_chap, int btn, int slot, int item);

void load_page(struct Entities* entities, struct ItemArray* items, int chapter);

void fight_all(struct ItemArray* items, struct Entities* entities, struct Entity* player);

void player_pickup(struct Entity* player, struct ItemArray* items, int item);

void player_use(struct Entity* player, struct ItemArray* items);

void look_for_pickup();

void update_display();