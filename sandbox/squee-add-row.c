#include <fcntl.h>
#include <stdint.h>
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
    char *cols[argc];

    Database *db = squee_read_database_from_file2(argv[argc - 1]);
    squee_print_rows(db->table->row);

    int c = 0;
    for (int i = 1; i < argc - 1; i++) {
        // printf("add_row() number of cols [%i] [%s] \n", i, argv[i]);
        cols[c] = argv[i];
        c = c + 1;
    }

	char *cols_data1[] = {"John", "Doe", "42", "4.25"};
    Row *row = squee_create_row(db->table, cols_data1, 4);
    squee_append_row(db->table, row);

	char *cols_data2[] = {"Bob", "Cratchet", "35", "1.01"};
    row = squee_create_row(db->table, cols_data2, 4);
    squee_append_row(db->table, row);

    squee_print_rows(db->table->row);
    squee_write_database_to_file(argv[argc - 1], db);

    return(0);
}
