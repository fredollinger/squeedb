#include <stdio.h>
#include <fcntl.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new column1 column2 filename");
        printf("\n");
        return(0);
    }

    int i = 0;
    for(i = 0; i < argc - 1; i++) {
        printf("%i %s \n", i, argv[i]);
    }
    printf("\n file argc: %i i: %i %s \n", argc, i, argv[argc-1]);
    open(argv[argc - 1], O_RDWR | O_CREAT);

    return(0);
}
