// #include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

#include "squee-structures.h"

int main() {
	char *cols_header[] = {"First_Name", "2", "Last_Name", "2", "Age", "0", "Hourly_Rate", "1"};
	char *cols_data[] = {"John", "Doe", "42", "4.25"};
    Database *db = squee_new_empty_database();
    db->table = squee_new_table_with_header("Employees", 0, 8, cols_header);
    squee_print_header(db->table->header);
    Row *row = squee_create_row(db->table, cols_data, 8);
    squee_print_row(row);
}
