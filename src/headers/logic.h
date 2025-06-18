#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "entityArray.h"
#include "entity.h"
#include "itemArray.h"
#include "inventory.h"
#include "display.h"
#include "chapters.h"
#include "display.h"


enum BUTTON {
    NEW_CHAPTER,
    FIGHT,
    PICK_UP,
    DROP,
    USE,
    SLOT
};


void btn_logic(struct Entities* entities, struct Entity* player, struct ItemArray* items, int chapter, int btn, int slot, int item);

void load_page(struct Entities* entities, struct ItemArray* items, int chapter);

void fight_all(struct ItemArray* items, struct Entities* entities, struct Entity* player);

void player_pickup(struct Entity* player, struct ItemArray* items, int item);

void player_use(struct Entity* player, struct ItemArray* items);

void look_for_pickup();

void update_display(struct Entities* entities, struct Entity* player, struct ItemArray* items, int chapter, int btn, int slot, int item);


#endif