#ifndef SQUEE_STRUCTURES_H
#define SQUEE_STRUCTURES_H

// Datatypes

// The data type that the field holds
typedef enum { INT, FLOAT, STRING, DATE, HEAD, TAIL } Field_t;

typedef struct Header {
    char *field_name;
    Field_t field_t;
    struct Header *next;
} Header;

typedef struct Table {
    char *name;
    Header *header;
} Table;

// how to have more than one table?
typedef struct Database {
    Table *table;
} Database;

// Functions

// New Functions

Database* squee_new_database();
Header* squee_new_header(int begin, int end, char* cols[]);
Table* squee_new_table(char* name, int begin, int end, char* cols[]);

// Print Functions

void squee_print_header(Header*);
void squee_print_table(Table*);

#endif
