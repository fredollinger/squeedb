#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "squee-structures.h"

// Helper Functions

// Ensure an empty Header is correct
void check_empty_header(Header *header) {
    assert (SQUEE_HEAD == header->field_t);
    header = header->next;
    assert (SQUEE_TAIL == header->field_t);
}

// Ensure an empty Row is correct
void check_empty_row(Row *row) {
    assert (SQUEE_HEAD == row->field_t);
    row = row->next;
    assert (SQUEE_TAIL == row->field_t);
}

// Unit Tests
void test_squee_new_empty_header() {
    Header *header = squee_new_empty_header();
    check_empty_header(header);
    // TODO Delete Header
}

void test_squee_header_add_column() {
    // Setup
    Header *header = squee_new_empty_header();
    // Keep a pointer to the header as the header var will change after
    // each call of squee_header_add_column()
    Header *head = header;

    header = squee_header_add_column(header, "First Name", 2);
    header = squee_header_add_column(header, "Last Name", 2);
    header = squee_header_add_column(header, "Age", 0);
    header = squee_header_add_column(header, "Hourly Rate", 1);

    // Start testing
    assert (SQUEE_HEAD == head->field_t);

    Header *h = head->next;
    assert (2 == h->field_t);
    assert (0 == strcmp("First Name", h->field_name));

    h = h->next;
    assert (2 == h->field_t);
    assert (0 == strcmp("Last Name", h->field_name));

    h = h->next;
    assert (0 == h->field_t);
    assert (0 == strcmp("Age", h->field_name));

    h = h->next;
    assert (1 == h->field_t);
    assert (0 == strcmp("Hourly Rate", h->field_name));

    h = h->next;
    assert (SQUEE_TAIL == h->field_t);

    // Teardown
}

void test_squee_new_empty_row_list() {
    Row *row = squee_new_empty_row_list();
    check_empty_row(row);
}

void test_new_empty_database() {
    Database *db = squee_new_empty_database();
    check_empty_row(db->table->row);
    check_empty_header(db->table->header);
}

// For now this is just a wrapper on malloc so no test is needed
void test_squee_new_empty_table() {
    return;
}

/*
void test_squee_new_table_with_header() {
	char *cols[] = {"John", "Doe", "42", "4.25"};
    Table *table = squee_new_table_with_header("Employees", 0, 4, cols);

    squee_print_header(table->header);

    Header *header = table->header->next;
    assert (0 == strcmp("Employees", table->name));

    assert (SQUEE_HEAD == table->header->field_t);
    assert (0 == strcmp("John", header->field_name));

    header = header->next;
    printf("field name [%s] \n", header->field_name);
    // assert (0 == strcmp("Doe", header->field_name));

    header = header->next;
    printf("field name [%s] \n", header->field_name);
    // assert (0 == strcmp("42", header->field_name));

    header = header->next;
    assert (0 == strcmp("4.25", header->field_name));

    header = header->next;
    assert (SQUEE_TAIL == header->field_t);
}
*/

// squee_new_table_with_header begin: [2] end: [10]
/*
void test_squee_new_header_with_columns() {
	char *cols[] = {"John", "Doe", "42", "4.25"};
    int begin = 0;
    int end = 4;
    Header *header = squee_new_header_with_columns(begin, end, cols);
}
*/

int main() {
    test_squee_new_empty_header();
    test_squee_header_add_column();
    test_squee_new_empty_row_list();
    // test_squee_new_table_with_header();
}
