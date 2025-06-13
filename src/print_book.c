#include "print_book.h"

void print_book() {
    FILE *f = fopen(BOOK, "r");
    FILE *file = NULL;
    if (!f) {
        perror("Error opening file");
        exit(1);
    }
    struct stat st = {0};
    if(stat("src/export", &st) == -1) mkdir("src/export", 0700);
    char line[LINE_SIZE];
    while(fgets(line, sizeof(line), f)) {
        if (strstr(line, "<chapter") != NULL) {
            if(file != NULL) end_file(file);
            char id[128], title[256];
            sscanf(line, "<chapter id=\"%[^\"]\">%[^<]", id, title);
            file = create_file(id);
        }  
        print_line(file, line);
    }
    if(file) end_file(file);
    fclose(f);
}


FILE* create_file(char* id){    
    char filename[256];
    snprintf(filename, sizeof(filename), "src/export/%s.html", id);
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    init_file(file, id);
    return file;
}

void init_file(FILE* file, char* id) {
    char* html_init =
        "<!DOCTYPE html>\n"
        "<html lang=\"fr\">\n"
            "<head>\n"
            "<meta charset=\"utf-8\">\n"
            "<title> Chapitre %s </title>\n"
        "</head>\n"
        "<body>\n";
    fprintf(file, html_init, id);
}

void end_file(FILE* file) {
    fprintf(file, "</body>\n</html>\n");
    fclose(file);
}

void print_line(FILE* file, char* line) {
    if (strlen(line) < 3) return;
    char content[2048], balise[64], id[16];
    sscanf(line, "%*[^>]>%[^<]", content);

    sscanf(line, "<%[^> ]", balise);
    if(strcmp(balise, "chapter") == 0) strcpy(balise, "h1");
    if(strcmp(balise, "choice") == 0) strcpy(balise, "p");

    fprintf(file, "<%s>%s", balise, content);
    if(strstr(line, "<a")) {
        sscanf(line, "%*[^\"]\"%[^\"]", id);
        fprintf(file, "<a href=\"%s.html\">Chapitre %s</a>", id, id);
    }
    fprintf(file, "</%s>\n", balise);
}

