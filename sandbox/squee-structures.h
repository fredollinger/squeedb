#ifndef SQUEE_STRUCTURES_H
#define SQUEE_STRUCTURES_H

// Datatypes

// Delimiters
#define SQUEE_UNIT_SEPARATOR 0x1F
#define SQUEE_RECORD_SEPARATOR 0x1E
#define SQUEE_START_OF_TEXT 0x02
#define SQUEE_END_OF_TEXT 0x03
#define SQUEE_END_OF_FILE 0x04

// The data type that the field holds
typedef enum { SQUEE_INT, SQUEE_FLOAT, SQUEE_STRING, SQUEE_DATE, SQUEE_HEAD, SQUEE_TAIL } Field_t;

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
Database* squee_new_empty_database();

// Table Creation
Table* squee_new_empty_table();
Table* squee_new_table(char* name, int begin, int end, char* cols[]);

// Header Creation
Header* squee_new_empty_header();
Header* squee_new_header(int begin, int end, char* cols[]);
Header* squee_header_add_column(Header *last, char *header_name, int field_type);

// Print Functions
void squee_print_header(Header*);
void squee_print_table(Table*);

#endif
