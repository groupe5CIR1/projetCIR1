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


bool btn_logic(struct Entities* entities, struct Entity* player, struct ItemArray* items, int chapter, int btn, int slot, int item);

void load_page(struct Entities* entities, struct ItemArray* items, int chapter);

void fight_all(struct ItemArray* items, struct Entities* entities, struct Entity* player, int chapter);

void player_pickup(struct Entity* player, struct ItemArray* items, int item, int chapter);

void player_use(struct Entity* player, struct ItemArray* items, int chapter);

void look_for_pickup();



#endif