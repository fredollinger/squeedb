#ifndef SQUEE_STRUCTURES_H
#define SQUEE_STRUCTURES_H

// Datatypes

// Delimiters
#define SQUEE_UNIT_SEPARATOR 0x1F
#define SQUEE_RECORD_SEPARATOR 0x1E
#define SQUEE_UNIT_SEPARATOR    0x1F
#define SQUEE_RECORD_SEPARATOR  0x1E
#define SQUEE_START_HEADER      0x02
#define SQUEE_END_HEADER        0x03
#define SQUEE_START_ROW         0x04
#define SQUEE_END_ROW           0x05
#define SQUEE_END_FILE       0x06

// The data type that the field holds
typedef enum { SQUEE_INT, SQUEE_FLOAT, SQUEE_STRING, SQUEE_DATE, SQUEE_DATA, SQUEE_HEAD, SQUEE_TAIL } Field_t;

typedef struct Row {
    struct Row *next;
    struct RowNode *next_row_node;
    Field_t field_t;
    int id;
} Row;

typedef struct RowNode {
    struct RowNode *next;
    Field_t field_t;
    union {
        int i;
        float f;
        char* s;
        uint64_t dt;
    } data;
} RowNode;

typedef struct Header {
    char *field_name;
    Field_t field_t;
    struct Header *next;
} Header;

typedef struct Table {
    char *name;
    Header *header;
    Row *row;
    int row_id; // the id that the next inserted row is going to get
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
Table* squee_new_table_with_header(char* name, int begin, int end, char* cols[]);

// Header Creation
Header* squee_new_empty_header();
Header* squee_new_header(int begin, int end, char* cols[]);
Header* squee_header_add_column(Header *last, char *header_name, int field_type);

// ROW CREATION
Row* squee_new_empty_row();
RowNode* squee_new_empty_row_node();
// Add a new row to a table
// Row* squee_add_row(Table *table, char* cols[], int len);
// Create a new free floating row
Row* squee_create_row(Table *table, char* cols[], int len);
// given a table, append a row onto it
void squee_append_row(Table *table, Row *row);

// Print Functions
void squee_print_field_type(Field_t field_t);
void squee_print_header(Header*);
void squee_print_table(Table*);
void squee_print_row(Row *row);
void squee_print_rows(Row *row);
void squee_print_row_node(RowNode *node);

// IO
Database* squee_read_database_from_file(char *file);
int squee_write_database_to_file(char *file, Database *db);

#endif
