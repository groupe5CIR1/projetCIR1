#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 512

void print_line(FILE *file, char* line);

FILE* create_file(char* filename);
