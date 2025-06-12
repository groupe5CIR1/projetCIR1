#include "main.h"

void main(void) {

}

FILE* create_file(char* filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de la création du fichier");
        return 1;
    }
    return file;
}