#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "print_book.h"
#include "logic.h"
#include "entityArray.h"

#define PORT 8080

float random();

int extract_chapter(char *buffer);

int extract_item(char *buffer);

int extract_slot(char* buffer);

void send_response(int socket, const char *message);