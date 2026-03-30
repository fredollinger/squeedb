#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "squee-structures.h"

Header* squee_new_header(char* cols[], int size) {
    // TODO loop through all of them

    Header *header = (Header*)malloc(sizeof(Header) + 1);
    header->next = NULL;
    for (int i = begin; i <= size; i++) {
        Header *neu = (Header*)malloc(sizeof(Header) + 1);
        neu->next = NULL;
        printf("col: %s \n", cols[i]);
        strcpy(neu->field_name, cols[i]);
        header->next = neu;
    }
    return header;
}

Table* squee_new_table(int begin, int end, char* cols[]) {
    Table *tbl = (Table*) malloc(sizeof(Table));

    printf("squee_new_table() begin: %i, end: %i \n", begin, end);

    for (int i = begin; i <= end; i++) {
        printf("col: %s \n", cols[i]);
    }
 
    return tbl;
}

void squee_print_header(Database *db) {
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
