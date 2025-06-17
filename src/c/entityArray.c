/*
EntityArray is a dynamic array storing all the entities in the game (including the player, monsters and ennemies).
Newly created entities should be added to this array, and dead entities should be removed from this array.
Note that this array only stores entities, regardless of their loaded tag. See LoadedEntities array for more information on the loaded tag.
*/


#include "../headers/entityArray.h"

struct EntityArray* init_entity_array() {
    struct EntityArray* ntt_arr = malloc(sizeof(struct EntityArray));
    if(ntt_arr == NULL) {
        perror("Out of Memory error : failed to allocate entity array struct");
        exit(1);
    }
    ntt_arr->entity_array = malloc(2*sizeof(struct Entity));
    if(ntt_arr->entity_array == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        free(ntt_arr);
        exit(1);
    }
    ntt_arr->size = 0;
    ntt_arr->capacity = 2;
    return (struct EntityArray*) ntt_arr;
}

void add_entity_array(struct EntityArray* Arr, struct Entity* entity) {
    if(Arr->size >= Arr->capacity) {
        int new_capacity = 2*Arr->capacity;
        struct Entity* newEntityArr = malloc(new_capacity*sizeof(struct Entity));
        if(newEntityArr == NULL) {
            perror("Out of Memory error : could not allocate entity array for a resize\n");
            exit(1);
        }
        for(int i=0; i < Arr->size; i++) {
            newEntityArr[i] = Arr->entity_array[i];
        }
        free(Arr->entity_array);
        Arr->entity_array = newEntityArr;
        Arr->capacity = new_capacity;
    }
    Arr->entity_array[Arr->size] = *entity;
    Arr->size++;
}

struct Entity* get_entity_array(struct EntityArray* Arr, int uid) {
    for (int i=0; i < Arr->size; i++) {
        if (Arr->entity_array[i].uid == uid) {
            return &Arr->entity_array[i];
        }
    }
    return NULL;
}

void free_entity(struct ItemArray* items, struct Entity* entity) {
    if (entity == NULL) return;
    if (entity->armor != NULL) free_armor(entity->armor);  //à faire
    if (entity->inventory != NULL) free_inventory(items, entity->inventory);
}

void remove_entity_array(struct ItemArray* items, struct EntityArray* Arr, int uid) {
    if (Arr == NULL || Arr->size == 0) return;
    for (int i=0; i < Arr->size; i++) {
        if (Arr->entity_array[i].uid == uid) {
            free_entity(items, &Arr->entity_array[i]);
            for (int j = i; j < Arr->size - 1; j++) {
                Arr->entity_array[j] = Arr->entity_array[j + 1];
            }
            memset(&Arr->entity_array[Arr->size - 1], 0, sizeof(struct Entity));    //clear last element (now duplicate)
            Arr->size--;
            return;
        }
    }
}

void free_entity_array(struct ItemArray* items, struct EntityArray* Arr) {
    if (Arr == NULL) return;
    if (Arr->entity_array != NULL) {
        for (int i=0; i < Arr->size; i++) {
            if (Arr->entity_array[i].inventory != NULL) {
                free_inventory(items, Arr->entity_array[i].inventory);
            }
            if (Arr->entity_array[i].armor != NULL) {
                free_armor(Arr->entity_array[i].armor);     //à faire
            }
        }
        free(Arr->entity_array);
    }
    free(Arr);
}


/*
LoadedEntities is a dynamic array storing all the loaded entities, i.e. all the entities on one html page.
Those entities are tagged with the boolean "loaded" (true = loaded, false = not loaded).
Note that newly created entities should always be loaded, and leaving a page should unload all entities on that page and attempt to load new ones.
The player is ofc not affected by page changes, and should always be loaded.
*/

struct LoadedEntities* init_loaded_entity_array() {
    struct LoadedEntities* loaded_ntts = malloc(sizeof(struct LoadedEntities));
    if(loaded_ntts == NULL) {
        perror("Out of Memory error : failed to allocate loaded entity array struct");
        exit(1);
    }
    loaded_ntts->loaded_entities = malloc(2*sizeof(struct Entity));
    if(loaded_ntts->loaded_entities == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        free(loaded_ntts);
        exit(1);
    }
    loaded_ntts->size = 0;
    loaded_ntts->capacity = 2;
    return (struct LoadedEntities*) loaded_ntts;
}

void load_entity(struct LoadedEntities* Arr, struct Entity* entity) {
    if(Arr->size >= Arr->capacity) {
        int new_capacity = 2*Arr->capacity;
        struct Entity* newEntityArr = malloc(new_capacity*sizeof(struct Entity));
        if(newEntityArr == NULL) {
            perror("Out of Memory error : could not allocate entity array for a resize\n");
            exit(1);
        }
        for(int i=0; i < Arr->size; i++) {
            newEntityArr[i] = Arr->loaded_entities[i];
        }
        free(Arr->loaded_entities);
        Arr->loaded_entities = newEntityArr;
        Arr->capacity = new_capacity;
    }
    Arr->loaded_entities[Arr->size] = *entity;
    Arr->size++;
    entity->loaded = true;
}

void unload_entity(struct LoadedEntities* Arr, int uid) {
    if (Arr == NULL || Arr->size == 0) return;
    for (int i=0; i < Arr->size; i++) {
        if (Arr->loaded_entities[i].uid == uid) {
            Arr->loaded_entities[i].loaded = false;
            for (int j=i; j < Arr->size - 1; j++) {
                Arr->loaded_entities[j] = Arr->loaded_entities[j+1];
            }
            Arr->size--;
            return;
        }
    }
}

void free_loaded_entities(struct ItemArray* items, struct LoadedEntities* Arr) {
    if (Arr == NULL) return;
    if (Arr->loaded_entities != NULL) {
        for (int i=0; i < Arr->size; i++) {
            if (Arr->loaded_entities[i].inventory != NULL) {
                free_inventory(items, Arr->loaded_entities[i].inventory);
            }
            if (Arr->loaded_entities[i].armor != NULL) {
                free_armor(Arr->loaded_entities[i].armor);     //à faire
            }
        }
        free(Arr->loaded_entities);
    }
    free(Arr);
}

