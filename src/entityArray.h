#ifndef ENTITY_ARRAY
#define ENTITY_ARRAY

#include <stdio.h>

struct Entities {
    struct EntityArray* entityArray;
    struct LoadedEntities* loadedEntities;
};

struct EntityArray {
    struct Entity* entity_array;
    int size;
    int capacity;
};

struct Entity* init_entity_array();
void add_entity_array(struct Entity** array, struct Entity* entity);
void remove_entity_array(struct Entity** array, struct Entity* entity);
struct Entity* get_entity_array(struct Entity** array, int uid);


struct LoadedEntities {
    struct Entity* loaded_entities;
    int size;
    int capacity;
};

struct Entity* init_loaded_entity_array();
void load_entity(struct Entity** array, struct Entity* entity);
void unload_entity(struct Entity** array, struct Entity* entity);

#endif