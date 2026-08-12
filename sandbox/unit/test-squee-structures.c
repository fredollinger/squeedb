#include <assert.h>
#include <inttypes.h>

#include "squee-structures.h"

void test_header() {
    Header *header = squee_new_empty_header();
    Header *next = header->next;
    assert (SQUEE_HEAD == header->field_t);
    assert (SQUEE_TAIL == next->field_t);
}

int main() {
    test_header();
}
