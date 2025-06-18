/*
Manages all entities (both players and ennemies), including creation, damaging.
For armor management, see armor.c
For inventory management, see inventory.c
*/

#include "../headers/entity.h"


struct Entity* create_entity(struct Entities* entities, int type) {
    struct Entity* entity = malloc(sizeof(struct Entity));
    if (entity == NULL) {
        perror("Out of Memory error : failed to allocate memory for entity");
        exit(EXIT_FAILURE);
    }
    float health;
    float damage;
    int uid = get_new_uid(entities->entityArray);
    switch (type) {
        case PLAYER:
            uid = 0;
            health = 100.0;
            damage = 10.0;
            break;
        case MONSTER:
            health = 70.0;
            damage = 7.0;
            break;
        case ENNEMY:
            health = 100.0;
            damage = 12.0;
            break;
        default:
            free(entity);
            break;
    }
    entity->uid = uid;
    entity->loaded = true;
    entity->type = type;
    entity->health = health;
    entity->defaultDamage = damage;
    entity->shield = false;
    entity->armor = NULL;
    entity->inventory = init_slots();
    add_entity_array(entities->entityArray, entity);
    load_entity(entities->loadedEntities, entity);
    return (struct Entity*) entity;
}

int get_new_uid(struct EntityArray* Arr) {
    int max_uid = 0;
    int entity_uid;
    for (int i=0; i < Arr->size; i++) {
        entity_uid = Arr->entity_array[i].uid;
        if (max_uid < entity_uid) max_uid = entity_uid;
    }
    return max_uid + 1;
}

void damage(struct ItemArray* items, struct Entity* attacker, struct Entity* defender) {
    float item_multiplier = 1;
    float armor_reduction = 1;
    float random_factor = 0.8 + 0.2 * randomizer();
    struct Inventory* att_inv = attacker->inventory;
    struct Armor* def_armor = defender->armor;
    if (att_inv->weapon > -1) {
        struct Item* weapon = &att_inv->slots[att_inv->weapon];
        item_multiplier = weapon->multiplier;
        update_item_dura(items, att_inv);
    }
    if (def_armor) {
        armor_reduction = def_armor->resistance;
        def_armor->durability -= 5 * (float)randomizer();  //update_armor_dura à faire
    }
    defender->health -= attacker->defaultDamage * item_multiplier * armor_reduction * random_factor;
}

void fight(struct ItemArray* items, struct Entities* entities, struct Entity* player, struct Entity* ennemy) {
    printf("Player turn !\n");
    damage(items, player, ennemy);
    if(ennemy->health <= 0){
        death(items, entities, ennemy);
    }
    printf("player hp : %f\n", player->health);
    printf("ennemy hp : %f\n", ennemy->health);
    sleep(0.1);
    printf("Ennemy turn !\n");
    damage(items, ennemy, player);
    if(player->health <=0){
        death(items, entities, player);
    }
    printf("player hp : %f\n", player->health);
    printf("ennemy hp : %f\n", ennemy->health);
}
 
void death(struct ItemArray* items, struct Entities* entities, struct Entity* dead_guy_lol_sounds_like_a_skill_issue) {
    char* type;
    switch (dead_guy_lol_sounds_like_a_skill_issue->type) {
        case MONSTER: type = "Monster"; break;
        case ENNEMY: type = "Ennemy"; break;
        default: type = "Unknown entity"; break;
    }
    printf("%s died !\n", type);
    struct Inventory* inv = dead_guy_lol_sounds_like_a_skill_issue->inventory;
    for(int i=0; i < inv->size; i++){
        drop_item(dead_guy_lol_sounds_like_a_skill_issue->inventory, &inv->slots[i]);
    }
    unload_entity(entities->loadedEntities, dead_guy_lol_sounds_like_a_skill_issue->uid);
    remove_entity_array(items, entities->entityArray, dead_guy_lol_sounds_like_a_skill_issue->uid);
    //update_fight_image
}


