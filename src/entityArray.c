#include "entityArray.h"
#include "entity.h"

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
        struct Entity* newEntityArr = malloc(2*Arr->capacity*sizeof(struct Entity));
        for(int i=0; i < Arr->capacity; i++) {
            newEntityArr[i] = Arr->entity_array[i];
        }
    }
}
