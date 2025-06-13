#include "main.h"

void main(void) {
    FILE *f = fopen(BOOK, "r");
    FILE *file;
    if (!f) {
        perror("Error opening file");
        exit(1);
    }
    char line[LINE_SIZE];
    while(fgets(line, sizeof(line), f)) {
        if (strstr(line, "<chapter") != NULL) {
            if(file != NULL){
                fclose(file);
            }
            char id[128];
            char title[256];
            sscanf(line, "<chapter id=\"%[^\"]\">%[^<]", id, title);
            file = create_file(id);
        }  
        print_line(&file, line);
    }
    fclose(file);
    fclose(f);
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

void print_line(FILE* file, char* line) {
    char content[512], balise[64], id[16];
    sscanf(line, "%*[^>]>%[^<]", content);

    sscanf(line, "<%[^> ]", balise);
    if(strcmp(balise, "chapter") == 0) strcpy(balise, "h1");
    if(strcmp(balise, "choice") == 0) strcpy(balise, "p");

    fprintf(file, "<%s>%s", balise, content);
    if(strstr(line, "<a")) {
        sscanf(line, "%*[^\"]\"%[^\"]", id);
        fprintf(file, "<a href=\"%s\">Chapitre %s</a>", id, id);
    }
    fprintf(file, "</%s>\n", balise);
}