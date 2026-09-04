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
    // fko
    // TODO Need to actually create the columns from argv so that we weed out the 
    // type because squee_new_table_with_header() should only have columns like:
    // First_Name, Last_Name, Age, Hourly_Rate
    /*
    for (int i = begin; i < end; i = i + 2) {
        // here we need to add this to cols[]
    }
    */
    db->table = squee_new_table_with_header(argv[1], 2, (argc - 1) / 2, argv);
    printf("create table [%s] [%i] [%i] [%s]", argv[1], 2, argc -1, argv[0]);
    //squee_print_header(db->table->header);
    // squee_print_rows(db->table->row);
    squee_write_database_to_file(argv[argc - 1], db);

    return(0);
}
