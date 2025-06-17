#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "print_book.h"

#define PORT 8080

float random();

void send_response(int socket, const char *message);