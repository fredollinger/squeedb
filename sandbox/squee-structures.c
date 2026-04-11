#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "squee-structures.h"

// insert the new item right after the head
/*
node* linked_list_insert(int key, node *ptr) {
    node *neu = malloc(sizeof(node));
    neu->key = key;
    neu->next = ptr->next;
    ptr->next = neu;
    return neu;
}
*/

Header* squee_new_header(int begin, int end, char* cols[]) {
    Header *head = (Header*)malloc(sizeof(Header));
    Header *tail = (Header*)malloc(sizeof(Header));
    head->next = tail;
    head->field_t = SQUEE_HEAD;
    tail->field_t = SQUEE_TAIL;
    tail->next = NULL;
    head->field_name = NULL;
    tail->field_name = NULL;
    Header *curr = head;

    for (int i = begin; i < end; i++) {
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[1]) + 1);
        // TODO Once we get a real parser, we won't just assume that this is INT
        neu->field_t = SQUEE_INT;
        strcpy(neu->field_name, cols[i]);
        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;
    }
    return head;
}

Table* squee_new_table(char *name, int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    size_t name_len = strlen(name);
    tbl->name = (char*)malloc(name_len + 1);
    strncpy(tbl->name, name, name_len);
    tbl->header = squee_new_header(begin + 2, end, cols);
    return tbl;
}

// Given the field type print a header
void squee_print_field_type(Header *hdr) {
    printf(" squee_print_field_type STUB ");
    switch(hdr->field_t){
        case SQUEE_INT:
            printf("INT");
            break;
        default:
            printf("UK");
            break;
    }
}

void squee_print_header(Header *hdr) {
    Header *hdr_p = hdr;
    while (NULL != hdr_p) {
        if (hdr_p->field_t == SQUEE_INT) {
            printf("main(): Field Name: %s ", hdr_p->field_name);
            squee_print_field_type(hdr);
            printf("\n");
        }
        hdr_p = hdr_p->next;
    }
}

Database* squee_new_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}

void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}
