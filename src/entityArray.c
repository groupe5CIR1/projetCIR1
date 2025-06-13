#include "entityArray.h"
#include "entity.h"

struct Entity* init_entity_array() {
    struct Entity* array = malloc(2*sizeof(struct Entity));
    if(array == NULL) {
        perror("Out of Memory error : failed to allocate entity array");
        exit(1);
    }
    return array;
}

