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

    printf("add_row [%i] \n", argc);
    printf("\nBEGIN squee-add-row.c\n");
    Database *db = squee_read_database_from_file(argv[argc - 1]);
    // squee_print_header(db->table->header);

    //Row *row = squee_add_row(db->table, argv + 1, argc - 2);
    // printf("add_row() number of cols [%i] \n", argc - 2);
    int c = 0;
    for (int i = 1; i < argc - 1; i++) {
        printf("add_row() number of cols [%i] [%s] \n", i, argv[i]);
        cols[c] = argv[i];
        c = c + 1;
    }

	char *cols_data[] = {"John", "Doe", "42", "4.25"};
    // TODO do not hard code
    Row *row = squee_create_row(db->table, cols_data, 4);
    // squee_print_row(row);
    printf("\nEND squee-add-row.c\n");
    
    // squee_append_row(db->table, row);

    // squee_print_row_node(row->next_row_node);
    // squee_print_row(db->table->row);
    //printf("\n");

    //squee_write_database_to_file(argv[argc - 1], db);


    return(0);
}
