#ifndef ITEM_ARRAY_H
#define ITEM_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"

struct ItemArray {
    struct Item* itemArray;
    int size;
    int capacity;
};

struct ItemArray init_item_array();
void add_item_array(struct ItemArray* items, struct Item* item);
void remove_item_array(struct ItemArray* items, struct Item* item);
void free_item_array(struct ItemArray* items);


#endif