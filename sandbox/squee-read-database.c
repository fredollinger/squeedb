#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

    printf("Reading database: [%s] \n", argv[1]);

    Database *db = squee_read_database_from_file(argv[1]);
    squee_print_header(db->table->header);

    return(0);
}
