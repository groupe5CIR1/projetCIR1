#ifndef ENTITY_ARRAY
#define ENTITY_ARRAY

struct Entity* init_entity_array();

void add_entity_array(struct Entity* array, struct Entity* entity);

void remove_entity_array(struct Entity* array, struct Entity* entity);

struct Entity* get_entity_array(struct Entity* array, int uid);

#endif