#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"


void write_after_balise(FILE* file, char* text, char* balise, int b_index);


void update_fight_image(FILE* file, int type, bool display);

void update_button(FILE* file, int btn, bool display);

void update_inventory(struct Inventory* inv, int chapter);

void clear_inventory(FILE* file);

char* create_inv_slot(struct Item* item, int i);

void pick_up_button(FILE* file, int id_number);

#endif