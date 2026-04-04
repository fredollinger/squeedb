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
    head->field_t = HEAD;
    tail->field_t = TAIL;
    tail->next = NULL;
    head->field_name = NULL;
    tail->field_name = NULL;
    Header *curr = head;

    for (int i = begin; i < end; i++) {
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[1]) + 1);
        // TODO Once we get a real parser, we won't just assume that this is INT
        neu->field_t = INT;
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
    strlcpy(tbl->name, name, name_len);
    tbl->header = squee_new_header(begin + 2, end, cols);
    return tbl;
}

void squee_print_header(Header *hdr) {
    Header *hdr_p = hdr;
    while (NULL != hdr_p) {
        if (hdr_p->field_t == INT) {
            printf("main(): Field Name: %s \n", hdr_p->field_name);
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
