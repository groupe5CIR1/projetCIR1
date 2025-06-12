#include "main.h"

void main(void) {

}



FILE* create_file(char* id){
    char filename[128];
    snprintf(filename, sizeof(filename), "%s.html", id);
    FILE *file = fopen(id, "w");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    return file;
}

