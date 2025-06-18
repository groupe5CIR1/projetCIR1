#include "../headers/print_book.h"

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
    char id[128], title[256];
    while(fgets(line, sizeof(line), f)) {
        if (strstr(line, "<chapter") != NULL) {
            if (file) {
                add_game_display_file(file, id);
                add_js_file(file, id);
                end_file(file);
            }
            sscanf(line, "<chapter id=\"%[^\"]\">%[^<]", id, title);
            file = create_file(id);
        }  
        if (file) print_line(file, line);
    }
    if (file) {
        add_game_display_file(file, id);
        add_js_file(file, id);
        end_file(file);
    }
    fclose(f);
}


FILE* create_file(char* id) {    
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
        "   <head>\n"
        "       <link rel=\"stylesheet\" href=\"../common.css\">\n"
        "       <meta charset=\"utf-8\">\n"
        "   <title> Chapitre %s </title>\n"
        "</head>\n"
        "<body>\n"
        "<div id =\"texte\">";
    fprintf(file, html_init, id);   
}

void add_game_display_file(FILE* file, char* id) {
    int chapter = atoi(id);
    fprintf(file,
        "</div>\n"
        "<div id=\"combat_container\">\n"
        "    <div id=\"box_fight\">\n"
                //Toujours avoir style=\"display:none;\" à la fin de la balise pour que update_fight_image() fonctionne correctement
        "        <img src=\"../chevalier.png\" alt=\"chevalier\" id=\"chevalier\" style=\"display:block;\">\n"
        "        <img src=\"../ennemy.png\" alt=\"ennemy\" id=\"ennemy\" style=\"display:none;\">\n"
        "        <img src=\"../monster.png\" alt=\"monster\" id=\"monster\" style=\"display:none;\">\n"
        "    </div>\n"
        "    <div id=\"control_buttons\">\n"
        "        <button id=\"FIGHT\" onclick=\"sendButton(1, %d, -1)\">Fight</button>\n"
        "        <button id=\"PICKUP\" onclick=\"sendButton(2, %d, -1)\">Pick Up</button>\n"
        "        <button id=\"DROP\" onclick=\"sendButton(3, %d, -1)\">Drop</button>\n"
        "        <button id=\"USE\" onclick=\"sendButton(4, %d, -1)\">Use</button>\n"
        "    </div>\n"
        "    <div id=\"box_inventory\">\n"
        "        <h1>INVENTAIRE</h1> <br>\n"
        "        <img src=\"../inventory.png\" alt=\"inventaire\" id=\"inventaire\">\n"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item1\">"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item2\">"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item3\">"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item4\">"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item5\">"
        "        <img src=\"../chevalier.png\" alt=\"item\" id=\"item6\">"
        "    </div>\n"
        "</div>\n"
        , chapter, chapter, chapter, chapter
    );
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

void add_js_file(FILE* file, char* id) {
    int chapter = atoi(id);
    fprintf(file,
        "<script>\n"
        "    async function sendButton(btnNum, chapter, slot) {\n"
        "        try {\n"
        "            const response = await fetch('http://localhost:8080', {\n"
        "                method: 'POST',\n"
        "                headers: {'Content-Type': 'application/json'},\n"
        "                body: JSON.stringify({button: btnNum, chapter: chapter, slot: slot}),\n"
        "            mode: 'cors'\n"
        "            });\n"
        "            const result = await response.text();\n"
        "            console.log(\"Réponse:\", result);\n"
        "            if (result.includes(\"REFRESH\")) {location.reload();}\n"
        "        } catch (error) {\n"
        "            console.error(\"Erreur:\", error);\n"
        "        }\n"
        "    }\n"
        "    document.addEventListener('DOMContentLoaded', () => {\n"
        "        sendButton(0, %d, -1);\n"
        "    })\n"
        "</script>\n"
        , chapter
    );
}

void end_file(FILE* file) {
    fprintf(file, 
        "</body>\n"
        "</html>\n"
    );
    fclose(file);
}

