#include <stdlib.h>

#include "squee-structures.h"

Header* squee_new_header() {
    Header *header = (Header*)malloc(sizeof(Header));
    return header;
}

Database* squee_new_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    return db;
}
