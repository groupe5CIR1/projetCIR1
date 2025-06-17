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

void add_item_array(struct ItemArray* Arr, struct Item* item) {
    if(Arr->size >= Arr->capacity) {
        int new_capacity = 2*Arr->capacity;
        struct Item* newItemArr = malloc(new_capacity*sizeof(struct Item));
        if(newItemArr == NULL) {
            perror("Out of Memory error : could not allocate entity array for a resize\n");
            exit(1);
        }
        for(int i=0; i < Arr->size; i++) {
            newItemArr[i] = Arr->itemArray[i];
        }
        free(Arr->itemArray);
        Arr->itemArray = newItemArr;
        Arr->capacity = new_capacity;
    }
    Arr->itemArray[Arr->size] = *item;
    Arr->size++;
}

void remove_item_array(struct ItemArray* Arr, struct Item* item) {
    if (Arr == NULL || Arr->size == 0) return;
    for (int i=0; i < Arr->size; i++) {
        if (&Arr->itemArray[i] == item) {
            for (int j=i; j < Arr->size - 1; j++) {
                Arr->itemArray[j] = Arr->itemArray[j+1];
                free(&Arr->itemArray[i]);
            }
            Arr->size--;
            return;
        }
    }
}

void free_item_array(struct ItemArray* Arr) {
    if (Arr == NULL) return;
    for (int i=0; i < Arr->size; i++) {
        free(&Arr->itemArray[i]);
    }
    free(Arr->itemArray);
}

