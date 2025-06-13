/*
Fichier temporaire, copie de main.c pour ne pas avoir de problèmes au moment de commit/sync
*/

#include "main.h"

void main() {
}

void print_line(FILE* file, char* line) {
    char content[256], balise[64], id[16];
    sscanf(line, "%*[^>]>%[^<]", content);

    sscanf(line, "<%[^> >]", balise);
    if(strcmp(balise, "chapter") == 0) strcpy(balise, "h1");
    if(strcmp(balise, "choice") == 0) strcpy(balise, "p");

    fprintf(file, "<%s>%s", balise, content);
    if(strstr(line, "<a")) {
        sscanf(line, "%*[^\"]\"%[^\"]", id);
        fprintf(file, "<a href=\"%s\">Chapitre %s</a>", id, id);
    }
    fprintf(file, "</%s>\n", balise);
}

