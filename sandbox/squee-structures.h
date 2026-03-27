#ifndef SQUEE_STRUCTURES_H
#define SQUEE_STRUCTURES_H

typedef enum { INT, STRING } Field_t;

typedef struct Header {
    char *field_name;
    Field_t field_t;
    struct Header *next;
} Header;

typedef struct Table {
    Header *header;
} Table;

typedef struct Database {
    Table *table;
} Database;

Header* squee_new_header();
Table* squee_new_table();
Database* squee_new_database();

#endif
