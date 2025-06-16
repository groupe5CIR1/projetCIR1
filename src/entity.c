/*
Manages all entities (both players and ennemies), including creation, damaging.
For armor management, see armor.c
For inventory management, see inventory.c
*/

#include "entityArray.h"
#include "entity.h"
#include "inventory.h"

struct Entity entity_init(int type){
    float health;
    float damage;
    switch (type)
    {
    case PLAYER:
        health = 100.0;
        damage = 10.0;
        break;
    case MONSTER:
        health = 70.0;
        damage = 7.0;
        break;
    case ENNEMY:
        health = 90.0;
        damage = 9.0;
        break;
    }
    return (struct Entity) {.uid = NULL, .loaded = 1, .type = type , .health = health, .defaultDamage = NULL, .shield = 0, .armor = NULL, .inventory = NULL };
}

void damage(struct Entity* attacker, struct Entity* defender){
    float item_multiplier = 1;
    struct Inventory* inv = attacker->inventory;
    if(inv->weapon) {
        item_multiplier *= inv->slots[inv->weapon]->multiplier;
    }
    defender->health -= attacker->defaultDamage * item_multiplier;
    //ajouter armure
}

void fight(struct Entities* entities, struct Entity* player, struct Entity* ennemy){
    damage(player, ennemy);
    if(ennemy->health <= 0){
        death(entities, ennemy);
    }
    damage(ennemy, player);
    if(player->health <=0){
        death(entities, player);
    }
}

void death(struct Entities* entities, struct Entity* dead_guy_lol_sounds_like_a_skill_issue) {
    struct Inventory* Inventory = dead_guy_lol_sounds_like_a_skill_issue->inventory->slots;
    for(int i=0; i < Inventory->size; i++){
        drop_item(dead_guy_lol_sounds_like_a_skill_issue->inventory, &Inventory[i]);
    }
    unload_entity(entities->loadedEntities, dead_guy_lol_sounds_like_a_skill_issue->uid);
    remove_entity_array(entities->entityArray, dead_guy_lol_sounds_like_a_skill_issue->uid);
}


