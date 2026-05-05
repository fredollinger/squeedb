#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    printf("squeectl args [%i] \n", argc);
    if (1 >= argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squeectl");
        printf("\n");
        return(0);
    }

    printf("squeectl [%s] \n", argv[1]);

    return(0);
}
