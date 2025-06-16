#include "print_book.h"

float random(){
    return rand() / (float)RAND_MAX;
}

int main(void) {
    print_book();
    return 0;
}

