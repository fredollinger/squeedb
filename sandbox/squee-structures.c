#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "squee-structures.h"

Header* squee_new_header(int begin, int end, char* cols[]) {
    // TODO loop through all of them

    Header *header = (Header*)malloc(sizeof(Header) + 1);
    header->next = NULL;
    for (int i = begin; i < end; i++) {
        Header *neu = (Header*)malloc(sizeof(Header) + 1);
        neu->next = NULL;
        printf("squee_new_header(): [%s] \n", cols[i]);
        strcpy(neu->field_name, cols[i]);
        header->next = neu;
    }
    return header;
}

Table* squee_new_table(int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    tbl->header = squee_new_header(begin, end, cols);
    return tbl;
}

void squee_print_header(Header *hdr) {
    printf("squee_print_header() STUB \n");
}

Database* squee_new_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}

/*
void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}
*/
