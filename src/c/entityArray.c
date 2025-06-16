#include "../headers/entityArray.h"
#include "../headers/entity.h"

struct EntityArray init_entity_array() {
    struct Entity* array = malloc(2*sizeof(struct Entity));
    if(array == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        exit(1);
    }
    return (struct EntityArray) {array, 0, 2};
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

void free_entity(struct Entity* entity) {
    if (entity == NULL) return;
    //free armor & inventory
}

void remove_entity_array(struct EntityArray* Arr, int uid) {
    if (Arr == NULL || Arr->size == 0) return;
    for (int i=0; i < Arr->size; i++) {
        if (Arr->entity_array[i].uid == uid) {
            for (int j=i; j < Arr->size - 1; j++) {
                Arr->entity_array[j] = Arr->entity_array[j+1];
                free_entity(&Arr->entity_array[i]);
            }
            Arr->size--;
            return;
        }
    }
}

void free_entity_array(struct EntityArray* Arr) {
    if (Arr->entity_array == NULL) return;
    for (int i=0; i < Arr->size; i++) {
        free_entity(&Arr->entity_array[i]);
    }
    free(Arr->entity_array);
}



struct LoadedEntities init_loaded_entity_array() {
    struct LoadedEntities* array = malloc(2*sizeof(struct Entity));
    if(array == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        exit(1);
    }
    return (struct LoadedEntities) {array, 0, 2};
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

