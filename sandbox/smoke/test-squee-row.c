// #include <fcntl.h>
#include <stdint.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

#include "squee-structures.h"

int main() {
    // Test create empty row
    Row *row = squee_new_empty_row();
    squee_print_row(row);
}
