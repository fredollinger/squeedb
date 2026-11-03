#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "squee-structures.h"

int main() {
    char *file = "row.db";
	char *cols_names[] = {"First Name", "Last Name", "Age", "Hourly Rate"};
	char *datatypes[] = {"CHAR", "CHAR", "INT", "FLOAT"};
	char *cols_data[] = {"John", "Doe", "42", "20.20"};
	char *cols_data2[] = {"Robert", "Cratchet", "25", "1.25"};
    Database *db = squee_new_empty_database();

    Table *table2 = squee_create_table("Employees2", 4, cols_names, datatypes);
    squee_append_table(db, table2);

    Table *table = squee_create_table("Employees", 4, cols_names, datatypes);
    squee_append_table(db, table);

    Row *row = squee_create_row(table->header, cols_data, 4);

    FILE *fd = fopen(file, "w");
    if (NULL == fd) {
        printf("Error writing to [%s] errono \n", file);
        fclose(fd);
        return(1);
    }

    squee_write_single_row_to_file(row, fd);

    /*
    squee_append_row("Employees", db, row);
    row = squee_create_row(table->header, cols_data2, 4);
    squee_append_row("Employees", db, row);
    */


    /*
    squee_write_database_to_file("smoke.db", db);
    db = squee_read_database_from_file("smoke.db");
    squee_write_database_to_file("smoke2.db", db);
    */
}

