#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "squee-structures.h"

// Helper Functions

// Fixture Functions

Header* fixture_create_header() {
	char *cols[] = {"First Name", "CHAR", "Last Name", "CHAR", "Age", "INT", "Hourly Rate", "FLOAT"};
    Header *header = squee_new_header_with_columns(0, 4, cols);
    return header;
}

// Check Functions

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

void check_row(Row *row) {
    // printf("squee_print_row_node(): INT Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
	// char *cols[] = {"John", "Doe", "42", "4.25"};
    printf("check_row type [%i] \n", row->field_t);
    assert (SQUEE_DATA == row->field_t);
    RowNode *node = row->next_row_node;
    assert (SQUEE_HEAD == node->field_t);

    node = node->next;
    assert (SQUEE_STRING == node->field_t);
    printf("check_row 1st [%s] \n", node->data.s);
    assert (0 == strcmp("John", node->data.s));

    node = node->next;
    assert (SQUEE_STRING == node->field_t);
    assert (0 == strcmp("Doe", node->data.s));

    node = node->next;
    assert (SQUEE_INT == node->field_t);
    assert (42 == node->data.i);

    node = node->next;
    assert (SQUEE_FLOAT == node->field_t);
    printf("check_row() [%f] \n", node->data.f);
    assert (4.25 == node->data.f);

    node = node->next;
    assert (SQUEE_TAIL == node->field_t);
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

// Testing squee_new_header_with_columns()
void test_squee_new_header_with_columns() {
    Header *header = fixture_create_header();

    assert (SQUEE_HEAD == header->field_t);

    header = header->next;
    assert (0 == strcmp("First Name", header->field_name));
    printf("test_squee_new_header_with_columns() [%i] \n", header->field_t);
    assert (SQUEE_STRING == header->field_t);

    header = header->next;
    assert (0 == strcmp("Last Name", header->field_name));
    assert (SQUEE_STRING == header->field_t);

    header = header->next;
    assert (0 == strcmp("Age", header->field_name));
    assert (SQUEE_INT == header->field_t);
}

void test_squee_create_row() {
    Header *header = fixture_create_header();
	char *cols[] = {"John", "Doe", "42", "4.25"};
    Row *row = squee_create_row(header, cols, 4);
    check_row(row);
}

void test_squee_append_row() {
    // Table *tbl = (Table*) malloc(sizeof(Table));
    // FKO TODO
    // Row* squee_append_row(Table *table, Row *row);
}


int main() {
    test_squee_new_empty_header();
    test_squee_header_add_column();
    test_squee_new_empty_row_list();
    test_squee_new_header_with_columns();
    test_squee_create_row();
    test_squee_append_row();
    // test_squee_new_table_with_header();
}
