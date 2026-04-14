#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("Read database into memory \n");
        printf("Usage \n\n");
        printf("./squee-read-database filename.db");
        printf("\n");
        return(0);
    }

    int buffer_size = 10000;
    char buffer[buffer_size];

    printf("opening file %s \n", argv[argc - 1]);

    FILE *fd = fopen(argv[argc - 1], "r");
    if (NULL == fd) {
        printf("%s: Error opening to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    Table *tbl = squee_new_empty_table();

    while(fgets(buffer, buffer_size, fd)) {
        printf("%s", buffer);
    }

    // TODO READ Table Name

    fclose(fd);

    return(0);
}
