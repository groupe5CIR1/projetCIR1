/*
Creates the html files (print_book()), manages socket listener, and sends information to logic.c to run the logic of the game.
The listener part (socket and messages management) was mostly made by ChatGPT.
*/

#include "../headers/main.h"

int main(void) {
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
    
    while(1) {
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
        
        if (strstr(buffer, "\"button\":1")) {
            printf("Bouton 1 pressé\n");
            send_response(new_socket, "Bouton 1 reçu");
        } else if (strstr(buffer, "\"button\":2")) {
            printf("Bouton 2 pressé\n");
            send_response(new_socket, "Bouton 2 reçu");
        } else {
            send_response(new_socket, "Commande inconnue");
        }
        
        close(new_socket);
        memset(buffer, 0, 1024);
    }
    
    close(server_fd);
    return 0;
}




float random() {
    return rand() / (float)RAND_MAX;
}