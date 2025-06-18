/*
Logic to display the game.
Functions in this file are called whenever a page is refreshed, or whenever a button is clicked.
Note that the afomentionned button must have a tag indicating which action to execute.
In any case, the entities must be ticked, the game displayed and logic updated.

Note that this file does not manage the sockets that listen to the port 8080.
See "main.c" for more information. 
*/


#include "../headers/display.h"


//Inutile
void get_text(FILE* file, char* balise, int b_index) {

}


//Inutile
void write_after_balise(FILE* file,  char* text, char* balise, int b_index) { //ending balise only ex:</div> else risk of writing inside the content of a already existing balise
    // Lit tout le fichier en mémoire
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';

    // Cherche la b_index-ième occurrence de la balise
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

    // Construit le nouveau contenu
    size_t before_len = insert_point - content;
    size_t new_size = size + strlen(text);
    char* new_content = malloc(new_size + 1);

    strncpy(new_content, content, before_len);
    new_content[before_len] = '\0';
    strcat(new_content, text);
    strcat(new_content, insert_point);

    // Réécrit dans le fichier
    freopen(NULL, "w", file); // rouvre le même fichier en écriture (efface contenu)
    fwrite(new_content, 1, strlen(new_content), file);
    fflush(file); // Assure que tout est bien écrit

    free(content);
    free(new_content);
}


void update_fight_image(FILE* file, int type, bool display) {
    const char* id;
    switch (type) {
        case MONSTER: id = "monster"; break;
        case ENNEMY:  id = "ennemy";  break;
        case PLAYER:  id = "chevalier"; break;
        default: return;
    }

    // Lire tout le fichier
    fseek(file, 0, SEEK_END);
    long size = ftell(file);    //Taille du fichier
    rewind(file);
    char* content = malloc(size + 1);   //Contenu du fichier
    fread(content, 1, size, file);
    content[size] = '\0';

    //Cherche la balise
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "id=\"%s\"", id);
    char* img_tag = strstr(content, pattern);
    if (!img_tag) {
        free(content);
        return;
    }

    //Cherche le style (= toujours le dernier attribut avant '>')
    char* style_start = strstr(img_tag, "style=\"display:");
    char* style_end = strchr(img_tag, '>');
    if (!style_start || !style_end || style_start > style_end) {
        free(content);
        return;
    }

    long prefix_len = style_start - content;
    long suffix_pos = style_end - content;

    //Réécrit le fichier
    freopen(NULL, "w", file);
    fwrite(content, 1, prefix_len, file);
    fprintf(file, "style=\"display:%s;\"", display ? "block" : "none");
    fwrite(content + suffix_pos, 1, size - suffix_pos, file);

    free(content);
    fflush(file);
}

//Quasiment la même fonction que update_fight_image, à voir pour optimiser et avoir au final une seule fonction
void update_button(FILE* file, int btn, bool display) {
    const char* id;
    switch (btn) {
        case FIGHT: id = "FIGHT"; break;
        case PICK_UP:  id = "PICKUP";  break;
        case DROP:  id = "DROP"; break;
        case USE: id = "USE"; break;
        default: return;
    }

    // Lire tout le fichier
    fseek(file, 0, SEEK_END);
    long size = ftell(file);    //Taille du fichier
    rewind(file);
    char* content = malloc(size + 1);   //Contenu du fichier
    fread(content, 1, size, file);
    content[size] = '\0';

    //Cherche la balise
    char pattern[64];
    snprintf(pattern, sizeof(pattern), "id=\"%s\"", id);
    char* btn_tag = strstr(content, pattern);
    if (!btn_tag) {
        free(content);
        return;
    }

    //Cherche le style (= toujours le dernier attribut avant '>')
    char* style_start = strstr(btn_tag, "style=\"display:");
    char* style_end = strchr(btn_tag, '>');
    if (!style_start || !style_end || style_start > style_end) {
        free(content);
        return;
    }

    long prefix_len = style_start - content;
    long suffix_pos = style_end - content;

    //Réécrit le fichier
    freopen(NULL, "w", file);
    fwrite(content, 1, prefix_len, file);
    fprintf(file, "style=\"display:%s;\"", display ? "block" : "none");
    fwrite(content + suffix_pos, 1, size - suffix_pos, file);

    free(content);
    fflush(file);
}


void update_inventory(struct Inventory* inv, int chapter) {
    char* button;
    char filename[256];
    char* zero = chapter < 10 ? "0": "";
    snprintf(filename, sizeof(filename), "src/export/%s%d.html", zero, chapter);
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error opening file for new chapter");
        exit(1);
    }

    clear_inventory(file);
    for (int i=0; i < inv->size; i++) {
        button = create_inv_slot(&inv->slots[i], i);
        write_after_balise(file, button, "<br>", 0);
    }
    fclose(file);
}

void clear_inventory(FILE* file) {
    //Lit le contenu
    fseek(file, 0, SEEK_END);
    long size = ftell(file);    //Taille du contenu
    rewind(file);
    char* content = malloc(size + 1);   //content = contenu du fichier
    fread(content, 1, size, file);
    content[size] = '\0';

    //Cherche "id=inventaire"
    char* inv_start = strstr(content, "id=\"inventaire\"");
    if (!inv_start) {
        free(content);
        return;
    }

    //Cherche le début de la balise img
    char* img_start = inv_start;
    while (img_start > content && *img_start != '<') {
        img_start--;
    }

    //Cherche la balise </div> de fin
    char* div_end = strstr(inv_start, "</div>");
    if (!div_end) {
        free(content);
        return;
    }

    //Parties à conserver
    int before_len = (int)(img_start - content);
    int after_len = (int)(strlen(div_end));

    freopen(NULL, "w", file);
    fwrite(content, 1, before_len, file);
    fwrite(div_end, 1, after_len, file);
    
    fflush(file);
    free(content);
}

char* create_inv_slot(struct Item* item, int i) {
    char button[64];
    snprintf(
        button,
        sizeof(button),
        "        <img src=\"../%s.png\" alt=\"item\" id=\"item%d\">\n",
        item->name,
        i
    );
    return button[64];
}
void pick_up_button(FILE* file, int id_number){
    if(id_number> 4) return;
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "<button class=\"PICK_UP_%d\">", id_number);
    write_after_balise(file, buffer, "</div>", 5);
}