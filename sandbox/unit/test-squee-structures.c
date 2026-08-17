#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "squee-structures.h"

void test_squee_new_empty_header() {
    Header *header = squee_new_empty_header();
    Header *next = header->next;
    assert (SQUEE_HEAD == header->field_t);
    assert (SQUEE_TAIL == next->field_t);
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

void test_new_empty_row_list() {
    Row *row = squee_new_empty_row_list();
    assert (SQUEE_HEAD == row->field_t);
    row = row->next;
    assert (SQUEE_TAIL == row->field_t);
}

int main() {
    test_squee_new_empty_header();
    test_squee_header_add_column();
    test_new_empty_row_list();
}
