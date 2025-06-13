/*
Manages all entities (both players and ennemies), including creation, damaging.
For armor management, see armor.c
For inventory management, see inventory.c
*/

#include "entityArray.h"
#include "entity.h"

struct Entity entity_init(int type){
    float health;
    switch (type)
    {
    case PLAYER:
        health = 100.0;
        break;
    case MONSTER:
        health = 70.0;
        break;
    case ENNEMY:
        health = 90.0;
        break;
    }
    //il faudra init inventory et possiblement uid (shield et armor si on a le temps)
    return (struct Entity) {.uid = NULL, .loaded = 1, .type = type , .health = health, .defaultDamage = NULL, .shield = 0, };
}

