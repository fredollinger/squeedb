// #include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

#include "squee-structures.h"

int main() {
	char *cols[] = {"John", "Doe", "42", "4.25"};
    Database *db = squee_new_empty_database();
    db->table = squee_new_table_with_header("Employees", 0, 3, cols);
}
