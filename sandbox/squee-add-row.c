#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("Add a row to a database\n");
        printf("List the data then the filename.\n");
        printf("\n");
        printf("usage: \n");
        printf("\n");
        printf("./[%s] John Doe 42 4.25 filename.db", argv[0]);
        printf("\n");
        return(0);
    }

    printf("Reading database: [%s] \n", argv[argc - 1]);
    Database *db = squee_read_database_from_file(argv[argc - 1]);
    squee_print_header(db->table->header);
    // Row *row = squee_add_row(db->table, argv, argc - 1);

    //squee_print_row(row);

    // squee_print_header(db->table->header);

    return(0);
}
