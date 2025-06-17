#ifndef PRINT_BOOK
#define PRINT_BOOK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define LINE_SIZE 512
#define BOOK "src/book.txt"

void print_book();
FILE* create_file(char* filename);
void init_file(FILE* file, char* id);
void add_game_display_file(FILE* file, char* id);
void print_line(FILE *file, char* line);
void add_js_file(FILE* file, char* id);
void end_file(FILE* file);
#endif