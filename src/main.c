#include "main.h"

void main(void) {
    FILE *f = fopen("book.txt", "r");
    if (!f) {
        perror("Error opening file");
        exit(1);
    }
    char line[LINE_SIZE];
    while(fgets(line, sizeof(line), f)) {
        if (strstr(line, "<chapter") != NULL) {
            char id[128];
            char title[256];
            sscanf(line, "<chapter id=\"%[^\"]\">%[^<]", id, title);
            FILE* file = create_file(id);
            }  
        }
    }


FILE* create_file(char* id){    
    char filename[256];
    snprintf(filename, sizeof(filename), "export/%s.html", id);
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    return file;
}

