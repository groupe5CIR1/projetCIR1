/*
Creates the html files (print_book()), manages socket listener, and sends information to logic.c to run the logic of the game.
The listener part (socket and messages management) was mostly made by ChatGPT.
*/

#include "../headers/main.h"

int main(void) {
    printf("\nmain start\n");
    print_book();

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Serveur en écoute sur le port %d...\n", PORT);

    struct Entities entities;
    entities.entityArray = init_entity_array();
    entities.loadedEntities = init_loaded_entity_array();

    struct ItemArray items = init_item_array();

    struct Entity* player = create_entity(&entities, PLAYER);
    
    int chapter = 0;
    int btn, new_chapter, slot, item;
    bool refresh = true;
    char* message;
    char response[1024];
    while(true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        ssize_t bytes_read = read(new_socket, buffer, 1024);
        if (bytes_read < 0) {
            perror("read failed");
            close(new_socket);
            continue;
        }
        
        if (strstr(buffer, "OPTIONS")) {
            send_response(new_socket, "");
            close(new_socket);
            continue;
        }
        
        btn = -1;
        slot = -1;
        item = -1;
        if (strstr(buffer, "\"button\":0")) {   //on page loading
            printf("NEW_CHAPTER (0) : \n");
            message = "NEW_CHAPTER (0)";
            printf("current chapter : %d\n", chapter);
            new_chapter = extract_chapter(buffer);
            printf("new chapter : %d\n", new_chapter);
            refresh = chapter < new_chapter;
            if (refresh) {        //prevents reload exploits
                btn = NEW_CHAPTER;
                chapter = new_chapter;
                printf("success, loaded chapter %d\n\n", chapter);
            } else {
                printf("failed, no change for chapter %d\n\n", chapter);
            }
        }
        else if (strstr(buffer, "\"button\":1")) {
            printf("Bouton FIGHT pressé (1)\n");
            message = "Bouton FIGHT reçu (1)";
            btn = FIGHT;
        }
        else if (strstr(buffer, "\"button\":2")) {
            printf("Bouton PICK_UP pressé (2)\n");
            message = "Bouton PICK_UP reçu (2)";
            btn = PICK_UP;
            item = extract_item(buffer);
        }
        else if (strstr(buffer, "\"button\":3")) {
            printf("Bouton DROP pressé (3)\n");
            message = "Bouton DROP reçu (3)";
            btn = DROP;
        }
        else if (strstr(buffer, "\"button\":4")) {
            printf("Bouton USE pressé (4)\n");
            message = "Bouton USE reçu (4)";
            btn = USE;
        }
        else if (strstr(buffer, "\"button\":5")) {
            printf("Bouton SLOT pressé (5)\n");
            message = "Bouton SLOT reçu (5)";
            btn = SLOT;
            slot = extract_slot(buffer);
        }
        else {
            printf("Commande inconnue\n");
            message = "Commande inconnue";
        }

        refresh |= btn_logic(&entities, player, &items, chapter, btn, slot, item);      //btn forces a refresh
        if (refresh) {
            snprintf(response, sizeof(response), "REFRESH : %s", message);
        } else {
            snprintf(response, sizeof(response), "%s", message);
        }
        send_response(new_socket, response);
        
        close(new_socket);
        memset(buffer, 0, 1024);
    }
    
    close(server_fd);
    free_loaded_entities(&items, entities.loadedEntities);
    free_entity_array(&items, entities.entityArray);
    free(&entities);
    free_item_array(&items);
    return 0;
}


void send_response(int socket, const char *message) {
    char response[1024];
    snprintf(response, sizeof(response), 
        "HTTP/1.1 200 OK\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s", strlen(message), message);
    write(socket, response, strlen(response));
}


int extract_chapter(char *buffer) {
    const char *chapter_str = strstr(buffer, "\"chapter\":");
    if (chapter_str) {
        return atoi(chapter_str + 10); // "\"chapter\":"  = 10 char
    }
    return -1;
}

int extract_slot(char *buffer) {
    const char *slot_str = strstr(buffer, "\"slot\":");
    if (slot_str) {
        return atoi(slot_str + 6); // "\"slot\":"  = 6 char
    }
    return -1;
}

int extract_item(char *buffer) {
    const char *item_str = strstr(buffer, "\"item\":");
    if (item_str) {
        return atoi(item_str + 6); // "\"item\":"  = 6 char
    }
    return -1;
}

float randomizer() {
    return rand() / (float)RAND_MAX;
}