/*
Logic to display the game.
Functions in this file are called whenever a page is refreshed, or whenever a button is clicked.
Note that the afomentionned button must have a tag indicating which action to execute.
In any case, the entities must be ticked, the game displayed and logic updated.

Note that this file does not manage the sockets that listen to the port 8080.
See "main.c" for more information. 
*/


#include "display.h"


void get_text(FILE* file, char* balise, int b_index) {


}


void write_after_balise(FILE* file, const char* text, const char* balise, int b_index) { //ending balise only ex:</div> else risk of writing inside the content of a already existing balise
    // Lire tout le fichier en mémoire
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';

    // Chercher la b_index-ième occurrence de la balise
    int count = 0;
    char* pos = content;
    char* insert_point = NULL;

    while ((pos = strstr(pos, balise)) != NULL) {
        count++;
        if (count == b_index) {
            insert_point = pos + strlen(balise); // après la balise
            break;
        }
        pos += strlen(balise);
    }

    if (insert_point == NULL) {
        printf("Balise %s non trouvée %d fois.\n", balise, b_index);
        free(content);
        return;
    }

    // Construire le nouveau contenu
    size_t before_len = insert_point - content;
    size_t new_size = size + strlen(text);
    char* new_content = malloc(new_size + 1);

    strncpy(new_content, content, before_len);
    new_content[before_len] = '\0';
    strcat(new_content, text);
    strcat(new_content, insert_point);

    // Réécrire dans le fichier
    freopen(NULL, "w", file); // rouvre le même fichier en écriture (efface contenu)
    fwrite(new_content, 1, strlen(new_content), file);
    fflush(file); // s’assurer que tout est bien écrit

    // Libération mémoire
    free(content);
    free(new_content);
}