#include <stdlib.h>

#include "squee-structures.h"

/*
Header* squee_make_header() {
    Header header* = new (Database*)malloc(sizeof(Database));
}
*/

Database* squee_make_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}
