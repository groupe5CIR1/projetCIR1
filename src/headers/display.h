#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void get_text(FILE* file, char* balise, int b_index);
void write_after_balise(FILE* file, char* text, char* balise, int b_index);
void delete(FILE* file, char* text, char* balise, int b_index);


void update_fight_image(FILE* file, char* link);

void update_button(FILE* file, int btn);

#endif