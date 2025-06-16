#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void get_text(FILE* file, char* balise, int b_index);
void write(FILE* file, char* text, char* balise, int b_index);
void delete(FILE* file, char* text, char* balise, int b_index);

#endif