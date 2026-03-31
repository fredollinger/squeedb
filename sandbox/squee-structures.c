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
    tail->next = NULL;
    head->field_name = NULL;
    tail->field_name = NULL;

    for (int i = begin; i < end; i++) {
        printf("squee_new_header(): [%s] \n", cols[i]);
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[1]) + 1);
        strcpy(neu->field_name, cols[i]);
        neu->next = head->next;
        head->next = neu;
    }
    return head;
}

Table* squee_new_table(int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    tbl->header = squee_new_header(begin, end, cols);
    return tbl;
}

void squee_print_header(Header *hdr) {
    // printf("squee_print_header() STUB \n");
}

Database* squee_new_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}

void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}
