#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define LINE_SIZE 512
#define BOOK "book.txt"

void print_line(FILE *file, char* line);

FILE* create_file(char* filename);
