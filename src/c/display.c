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


//Ajoute "texte" après la "b_index"-ième balise fermante "balise". Toujours utiliser une balise fermante en paramètre, ex: </div>. L'indice commence à 1.
void write_after_balise(FILE* file, char* text, char* balise, int b_index) {
    if (b_index < 1) return;

    // Lit tout le contenu du fichier
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';

    // Recherche la balise spécifique de l'inventaire
    char* inventory_img = strstr(content, "<img src=\"../inventory.png\" alt=\"inventaire\" id=\"inventaire\">");
    if (!inventory_img) {
        printf("Balise inventaire introuvable\n");
        free(content);
        return;
    }

    // Si on cherche à insérer après la balise d'inventaire
    if (strcmp(balise, "<img src=\"../inventory.png\" alt=\"inventaire\" id=\"inventaire\">") == 0) {
        char* insert_pos = inventory_img + strlen("<img src=\"../inventory.png\" alt=\"inventaire\" id=\"inventaire\">");
        
        // Construit le nouveau contenu
        long before_len = insert_pos - content;
        char* new_content = malloc(before_len + strlen(text) + (size - before_len) + 1);
        
        memcpy(new_content, content, before_len);
        strcpy(new_content + before_len, text);
        strcpy(new_content + before_len + strlen(text), insert_pos);

        // Réécrit le fichier
        rewind(file);
        fwrite(new_content, 1, strlen(new_content), file);
        fflush(file);
        free(new_content);
    }
    else {
        // Cas général pour les autres balises (conservé de votre version originale)
        char* pos = content;
        int count = 0;
        char* insert_pos = NULL;
        
        while ((pos = strstr(pos, balise))) {
            count++;
            if (count == b_index) {
                insert_pos = pos + strlen(balise);
                break;
            }
            pos++;
        }

        if (insert_pos) {
            long before_len = insert_pos - content;
            char* new_content = malloc(before_len + strlen(text) + (size - before_len) + 1);
            
            memcpy(new_content, content, before_len);
            strcpy(new_content + before_len, text);
            strcpy(new_content + before_len + strlen(text), insert_pos);

            rewind(file);
            fwrite(new_content, 1, strlen(new_content), file);
            fflush(file);
            free(new_content);
        }
    }

    free(content);
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

//Raffraichit l'inventaire
void update_inventory(struct Inventory* inv, int chapter) {
    char* button;
    char filename[256];
    char* zero = chapter < 10 ? "0": "";
    snprintf(filename, sizeof(filename), "src/export/%s%d.html", zero, chapter);
    printf("editing file %s\n", filename);
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Error opening file for new chapter");
        exit(1);
    }

    clear_inventory(file);
    printf("cleared inventory file\n");
    fclose(file);
    FILE* f = fopen(filename, "r+");

    char* pattern = "<img src=\"../inventory.png\" alt=\"inventaire\" id=\"inventaire\">";
    for (int i=0; i < inv->size; i++) {
        button = create_inv_slot(&inv->slots[i], i);
        printf("adding text : %s\n", button);
        write_after_balise(f, button, pattern, 1);
        free(button);
    }
    fclose(f);
}

void clear_inventory(FILE* file) {
    printf("clearing inventory file\n");
    
    // Lit le contenu du fichier
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';

    // Trouve la section inventaire
    char* inv_start = strstr(content, "id=\"inventaire\"");
    if (!inv_start) {
        free(content);
        return;
    }

    // Trouve le début de la div parente
    char* div_start = inv_start;
    while (div_start > content && *div_start != '<') {
        div_start--;
    }

    // Trouve la fin de la section inventaire
    char* inv_end = strstr(inv_start, "</div>");
    if (!inv_end) {
        free(content);
        return;
    }
    inv_end += 6; // Après "</div>"

    // Construit le nouveau contenu en gardant la balise inventaire
    long before_len = div_start - content;
    long after_len = size - (inv_end - content);
    
    char* new_content = malloc(before_len + (inv_end - div_start) + after_len + 1);
    
    // Copie la partie avant
    memcpy(new_content, content, before_len);
    
    // Copie la balise inventaire complète (de <div...> à </div>)
    memcpy(new_content + before_len, div_start, inv_end - div_start);
    
    // Copie la partie après
    memcpy(new_content + before_len + (inv_end - div_start), inv_end, after_len);
    
    new_content[before_len + (inv_end - div_start) + after_len] = '\0';

    // Réécrit le fichier
    rewind(file);
    fwrite(new_content, 1, strlen(new_content), file);
    fflush(file);

    free(content);
    free(new_content);
}


char* create_inv_slot(struct Item* item, int i) {
    char* button = malloc(1024*sizeof(char));
    char* name;
    switch(item->name) {
        case ARME_INCROYABLE_SA_GRANMERE: name = "ARME_INCROYABLE_SA_GRANMERE"; break;
        case DEUXIEME_ARME_INCROYABLE_SA_GRANMERE: name = "DEUXIEME_ARME_INCROYABLE_SA_GRANMERE"; break;
        case ARME_INCASSABLE_C_EST_TROP_BI1_SAMERE: name = "ARME_INCASSABLE_C_EST_TROP_BI1_SAMERE"; break;
        case POTION_HEAL: name = "POTION_HEAL"; break;
        default: break;
    }
    snprintf(
        button,
        1024,
        "\n        <img src=\"../%s.png\" alt=\"item\" id=\"item%d\" style=\"position:relative; z-index:100\">\n",
        name,
        i
    );
    return button;
}



void pick_up_button(FILE* file, int id_number) {
    if(id_number> 4) return;
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "<button class=\"PICK_UP_%d\">", id_number);
    write_after_balise(file, buffer, "</div>", 5);
}

