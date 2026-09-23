#include <stddef.h>
#include <stdint.h>

#include "squee-structures.h"

int main() {
	char *cols_names[] = {"First Name", "Last Name", "Age", "Hourly Rate"};
	char *datatypes[] = {"CHAR", "CHAR", "INT", "FLOAT"};
	char *cols_data[] = {"John", "Doe", "42", "4.25"};
    Database *db = squee_new_empty_database();
    Table *table = squee_create_table("Employees", 4, cols_names, datatypes);
    squee_print_table(db->table);
    squee_append_table(db, table);
    squee_print_table(db->table);
    Row *row = squee_create_row(table->header, cols_data, 4);
    squee_print_table(db->table);
    squee_append_row("Employees", db->table, row);
    squee_write_database_to_file("smoke.db", db);
}
