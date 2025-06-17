#ifndef ENTITY_ARRAY_H
#define ENTITY_ARRAY_H

#include <stdio.h>

#include "entity.h"

struct Entities {
    struct EntityArray* entityArray;
    struct LoadedEntities* loadedEntities;
};

struct EntityArray {
    struct Entity* entity_array;
    int size;
    int capacity;
};

struct EntityArray init_entity_array();
void add_entity_array(struct EntityArray* array, struct Entity* entity);
void free_entity(struct Entity* entity);
void remove_entity_array(struct EntityArray* array, int uid);
struct Entity* get_entity_array(struct EntityArray* array, int uid);
void free_entity_array(struct EntityArray* array);


struct LoadedEntities {
    struct Entity* loaded_entities;
    int size;
    int capacity;
};

struct LoadedEntities init_loaded_entity_array();
void load_entity(struct LoadedEntities* array, struct Entity* entity);
void unload_entity(struct LoadedEntities* array, int uid);

#endif