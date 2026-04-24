#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new-database filename.db");
        printf("\n");
        return(0);
    }

    FILE *fd = fopen(argv[argc - 1], "w");
    if (NULL == fd) {
        printf("%s: Error writing to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    fprintf(fd, "SQUEE format 3");
    fclose(fd);

    return(0);
}
