#include <stdio.h>
#include <stdlib.h>

#include "squee-structures.h"

Header* squee_new_header() {
    Header *header = (Header*)malloc(sizeof(Header));
    return header;
}

Table* squee_new_table(int begin, int end, char* cols[]) {
    Table *tbl = (Table*) malloc(sizeof(Table));

    printf("squee_new_table() begin: %i, end: %i \n", begin, end);

    int i;
    for (i = begin; i <= end; i++) {
        printf("col: %s \n", cols[i]);
    }
 
    return tbl;
}

Database* squee_new_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}
