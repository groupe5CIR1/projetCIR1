#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"


void get_text(FILE* file, char* balise, int b_index);
void write_after_balise(FILE* file, char* text, char* balise, int b_index);
void delete(FILE* file, char* text, char* balise, int b_index);


void update_fight_image(FILE* file, int type, bool display);

void update_button(FILE* file, int btn, bool display);

#endif