#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new-table table_name column1 column2 filename.db");
        printf("\n");
        return(0);
    }

    Database *db = squee_new_empty_database();
    printf("argc [%i] \n", argc);
    db->table = squee_new_table_with_header(argv[1], 2, argc - 1, argv);
    // squee_print_row(db->table->row);
    
    // squee_write_database_to_file(argv[argc - 1], db);

    return(0);
}
