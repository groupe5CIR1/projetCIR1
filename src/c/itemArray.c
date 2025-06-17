/*
Manages the list of all the existing items in a dynamic array.
Note that this does not manage inventories, see "inventory.c" for more information.
*/

#include "../headers/itemArray.h"

struct ItemArray init_item_array() {
    struct Item* array = malloc(2*sizeof(struct Item));
    if(array == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        exit(1);
    }
    return (struct ItemArray) {array, 0, 2};
}

void add_item_array(struct ItemArray* items, struct Item* item) {
    if(items->size >= items->capacity) {
        int new_capacity = 2*items->capacity;
        struct Item* newItemArr = malloc(new_capacity*sizeof(struct Item));
        if(newItemArr == NULL) {
            perror("Out of Memory error : could not allocate entity array for a resize\n");
            exit(1);
        }
        for(int i=0; i < items->size; i++) {
            newItemArr[i] = items->itemArray[i];
        }
        free(items->itemArray);
        items->itemArray = newItemArr;
        items->capacity = new_capacity;
    }
    items->itemArray[items->size] = *item;
    items->size++;
}

void remove_item_array(struct ItemArray* items, struct Item* item) {
    if (items == NULL || items->size == 0) return;
    for (int i=0; i < items->size; i++) {
        if (&items->itemArray[i] == item) {
            for (int j=i; j < items->size - 1; j++) {
                items->itemArray[j] = items->itemArray[j+1];
                free(&items->itemArray[i]);
            }
            items->size--;
            return;
        }
    }
}

void free_item_array(struct ItemArray* items) {
    if (items == NULL) return;
    for (int i=0; i < items->size; i++) {
        free(&items->itemArray[i]);
    }
    free(items->itemArray);
}

