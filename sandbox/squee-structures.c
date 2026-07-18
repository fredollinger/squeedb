#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "squee-structures.h"

// HEADER METHODS
Header* squee_new_empty_header() {
    Header *head = (Header*)malloc(sizeof(Header));
    Header *tail = (Header*)malloc(sizeof(Header));
    head->next = tail;
    head->field_t = SQUEE_HEAD;
    tail->field_t = SQUEE_TAIL;
    tail->next = NULL;
    head->field_name = NULL;
    tail->field_name = NULL;
    return head;
}

Header* squee_header_add_column(Header *last, char *header_name, int field_type) {
    Header *neu = (Header*)malloc(sizeof(Header));
    neu->field_name = (char*)malloc(strlen(header_name) + 1);
    neu->field_t = field_type;
    strcpy(neu->field_name, header_name);
    neu->next = last->next;
    last->next = neu;
    return neu;
}

Header* squee_new_header_with_columns(int begin, int end, char* cols[]) {
    Header *head = squee_new_empty_header();
    Header *curr = head;
    char *endptr;
    int type = 0;

    printf("squee_new_header_with_columns() begin [%i] end [%i] \n", begin, end);

    for (int i = begin; i < end; i = i + 2) {
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[i]) + 1);
        type = strtol(cols[i + 1], &endptr, 10);
        neu->field_t = type;
        strcpy(neu->field_name, cols[i]);
        printf("squee_new_header_with_columns() [%s] \n", neu->field_name);
        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;
    }
    return head;
}

// Table Methods
Table* squee_new_empty_table() {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    return tbl;
}

// TODO FKO FIXME THIS IS BROKEN
Table* squee_new_table_with_header(char *name, int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    size_t name_len = strlen(name);
    tbl->name = (char*)malloc(name_len + 1);
    strncpy(tbl->name, name, name_len);
    tbl->header = squee_new_header_with_columns(begin, end, cols);
    squee_print_header(tbl->header);

    Row *tail_row = (Row*) malloc(sizeof(Row));
    tail_row->field_t = SQUEE_TAIL;
    tail_row->next_row_node = NULL;
    Row *head_row = (Row*) malloc(sizeof(Row));
    head_row->field_t = SQUEE_HEAD;
    head_row->next_row_node = NULL;
    head_row->next = tail_row;
    tbl->row = head_row;

    return tbl;
}

// ROW METHODS

Row* squee_create_row(Table *table, char* cols[], int len) {
    Row *row = squee_new_empty_row();
    row->id = -1;
    Header *hdr_p = table->header;
    RowNode *curr = row->next_row_node;
    long value; // used for string conversion
    char *endptr;

    printf("\n");
    int i = 0;
    while (NULL != hdr_p) {
        // TODO IF WE MEET THIS THEN WE NEED TO CONTINUE INSTEAD OF WHAT WE ARE DOING
        // if (SQUEE_TAIL != hdr_p->field_t && SQUEE_HEAD != hdr_p->field_t) {
            printf("squee_create_row(): %i cols [%s] \n", i, cols[i]);
            printf("squee_create_row(): Field Name: %s Field Type: %i ", hdr_p->field_name, hdr_p->field_t);
            squee_print_field_type(hdr_p->field_t);
            printf("\n");

            // FKO TODO remove the next 2
            hdr_p = hdr_p->next;
            continue;

            RowNode *neu = (RowNode*)malloc(sizeof(RowNode));
            neu->field_t = hdr_p->field_t;

            printf("squee_create_row(): Field Name: %s Field value: %s ", hdr_p->field_name, cols[i]);

            // TODO copy col data into the Row
            switch(neu->field_t) {
                case SQUEE_INT:
                    value = strtol(cols[i], &endptr, 10);
                    neu->data.i = (int)value;
                    break;
                case SQUEE_FLOAT:
                    value = strtof(cols[i], &endptr);
                    neu->data.f = (float)value;
                    break;
                case SQUEE_STRING:
                    neu->data.s = (char*)malloc(strlen(cols[i]));
                    strcpy(neu->data.s, cols[i]);
                    break;
                case SQUEE_DATE:
                    break;
                case SQUEE_HEAD:
                    break;
                case SQUEE_TAIL:
                    break;
                default:
                    break;
            }

            printf("squee_create_row() [%s] \n", hdr_p->field_name);
            neu->next = curr->next;
            curr->next = neu;
            curr = neu;

        // }
        i = i + 1;
        hdr_p = hdr_p->next;
    }

/*
    for (int i = 0; i < len; i = i + 1) {
       printf("squee_create_row() HEADER field_name [%s] \n", header->field_name);
       header = header->next; 
    }
*/

    return row;
}

Row* squee_new_empty_row() {
    Row *row = (Row*)malloc(sizeof(Row));
    RowNode *head = (RowNode*)malloc(sizeof(RowNode));
    RowNode *tail = (RowNode*)malloc(sizeof(RowNode));
    row->next_row_node = head;
    head->next = tail;
    head->field_t = SQUEE_HEAD;
    tail->field_t = SQUEE_TAIL;
    tail->next = NULL;
    return row;
}

/*
Row* squee_create_row(Table *table, char* cols[], int len) {
    Header *header_p = table->header->next->next;
    char *endptr; // used for string conversion
    long value; // used for string conversion

    // Header row that we need to add to the table
    Row *row_h = (Row*)malloc(sizeof(Row));
    RowNode *row = (RowNode*)malloc(sizeof(RowNode));
    row_h->field_t = SQUEE_HEAD;
    row_h->next_row_node = row;
    RowNode *last = row;

    for (int i = 0; i < len; i++) {
        // printf("squee_create_row() Header [%s] Type [%i] Item [%s] \n", header_p->field_name, header_p->field_t, cols[i]);
        row = (RowNode*)malloc(sizeof(RowNode));
        row->field_t = header_p->field_t;

        switch(row->field_t) {
            case SQUEE_INT:
                value = strtol(cols[i], &endptr, 10);
                row->data.i = (int)value;
                break;
            case SQUEE_FLOAT:
                value = strtof(cols[i], &endptr);
                row->data.f = (float)value;
                break;
            case SQUEE_STRING:
                row->data.s = (char*)malloc(strlen(cols[i]));
                strcpy(row->data.s, cols[i]);
                break;
            case SQUEE_DATE:
                break;
            case SQUEE_HEAD:
                break;
            case SQUEE_TAIL:
                break;
            default:
                break;
        }

        last->next = row;
        last = row;
        header_p = header_p->next;
    }
    
    // TODO: This allows for only a single row in a whole table. Need to implement more of an "insert row" here
    // once we get a single row working.

    // ADD A TAIL TO THE ROW
    // TODO need to remove this once we get insert working
    row = (RowNode*)malloc(sizeof(RowNode));
    row->field_t = SQUEE_TAIL;
    last->next = row;

    // TODO remove once we get code to insert the row instead
    table->row = row_h;

    return row_h;
}
*/

// TODO NOT DONE FKO
// Take a new row and add it to the linked list
void squee_append_row(Table *table, Row *row) {
    Row *prev = table->row;
    while (SQUEE_TAIL !=  row->next->field_t) {
        printf("squee_append_row(): %i \n", row->field_t);
        prev = row->next;
    }
    Row *last = prev->next;
    prev->next = row;
    row->next = last;
    table->row_id = table->row_id + 1;
    row->id = table->row_id;
}

// TODO NOT DONE FKO We probably need to rewrite this
Row* squee_add_row(Table *table, char* cols[], int len) {
    Header *header_p = table->header->next->next;
    char *endptr; // used for string conversion
    long value; // used for string conversion

    // Header row that we need to add to the table
    Row *row_h = (Row*)malloc(sizeof(Row));
    RowNode *row = (RowNode*)malloc(sizeof(RowNode));
    row_h->field_t = SQUEE_HEAD;
    row_h->next_row_node = row;
    RowNode *last = row;

    for (int i = 0; i < len; i++) {
        printf("squee_add_row() Item [%s] \n", cols[i]);
        // printf("squee_add_row() Header [%s] Type [%i] Item [%s] \n", header_p->field_name, header_p->field_t, cols[i]);
        row = (RowNode*)malloc(sizeof(RowNode));
        row->field_t = header_p->field_t;

        switch(row->field_t) {
            case SQUEE_INT:
                value = strtol(cols[i], &endptr, 10);
                row->data.i = (int)value;
                break;
            case SQUEE_FLOAT:
                value = strtof(cols[i], &endptr);
                row->data.f = (float)value;
                break;
            case SQUEE_STRING:
                row->data.s = (char*)malloc(strlen(cols[i] + 1));
                strcpy(row->data.s, cols[i]);
                break;
            case SQUEE_DATE:
                break;
            case SQUEE_HEAD:
                break;
            case SQUEE_TAIL:
                break;
            default:
                break;

        }
        last->next = row;
        last = row;
        header_p = header_p->next;
    }
    
    RowNode *tail = (RowNode*)malloc(sizeof(RowNode));
    tail->field_t = SQUEE_TAIL;
    last->next = tail;

    // TODO: This allows for only a single row in a whole table. Need to implement more of an "insert row" here
    // once we get a single row working.

    // TODO remove once we get code to insert the row instead
    table->row = row_h;

    return row_h;
}

void squee_print_row_node(RowNode *node) {
    // TODO This prints one row node actually, but we need to iterate through all the rows
    // TODO copy the row node instead of invalidating it
    if (NULL == node) return;
    RowNode *curr = node;
    while (SQUEE_TAIL != curr->field_t) {
        switch(curr->field_t) {
            case SQUEE_INT:
                printf("squee_print_row_curr(): INT Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
                break;
            case SQUEE_FLOAT:
                printf("squee_print_row_curr(): FLOAT Type [%i] Data [%f] \n", curr->field_t, curr->data.f);
                break;
            case SQUEE_STRING:
                printf("squee_print_row_curr(): STRING Type [%i] Data [%s] \n", curr->field_t, curr->data.s);
                break;
            case SQUEE_DATE:
                printf("squee_print_row_curr(): DATE Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
                break;
            case SQUEE_HEAD:
                printf("squee_print_row_curr(): HEAD Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
                break;
            case SQUEE_TAIL:
                printf("squee_print_row_curr(): TAIL Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
                break;
            default:
                break;
        }
        curr = curr->next;
    }
    printf("squee_print_row_node(): TAIL Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
}

// Given a row, find the last element (before the tail)
// DELETE ME
RowNode* squee_end_of_row(Row *row_h) {
    return NULL;
}

// TODO iterate through rows via row->next till we get to the tail
void squee_print_row(Row *row) {
    Row *curr = row;
    if (NULL == row) return;
    while (SQUEE_TAIL != curr->next->field_t) {
        printf("print_row() type [%i] \n", row->field_t);
        RowNode *node = curr->next_row_node;
        printf("print_row() node [%i] \n", node);
        squee_print_row_node(node);
        curr = curr->next;
    }
}

// Given the field type print a header
void squee_print_field_type(Field_t field_t) {
    switch(field_t){
        case SQUEE_INT:
            printf("INT");
            break;
        case SQUEE_FLOAT:
            printf("FLOAT");
            break;
        case SQUEE_STRING:
            printf("STRING");
            break;
        case SQUEE_DATE:
            printf("DATE");
            break;
        case SQUEE_HEAD:
            break;
        case SQUEE_TAIL:
            break;
        default:
            printf("UK");
            break;
    }
}

void squee_print_header(Header *hdr) {
    Header *hdr_p = hdr;
    while (NULL != hdr_p) {
        if (SQUEE_TAIL != hdr_p->field_t && SQUEE_HEAD != hdr_p->field_t) {
            printf("squee_print_header(): Field Name: %s Field Type: %i ", hdr_p->field_name, hdr_p->field_t);
            squee_print_field_type(hdr_p->field_t);
            printf("\n");
        }
        hdr_p = hdr_p->next;
    }
}

Database* squee_new_empty_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    db->table = squee_new_empty_table();
    db->table->row_id = 0;
    db->table->header = squee_new_empty_header();
    return db;
}

void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}

// IO
Database* squee_read_database_from_file(char *file) {
    printf("TODO NEED TO READ THE ROWS HERE \n");
    int buffer_size = 10000;
    int type = 0;
    char *endptr = NULL;
    char buffer[buffer_size];
    char *pbuffer = buffer;
    char *tok, *col, *type_s;
    char squee_start_of_text[2] = { SQUEE_START_OF_TEXT, '\0' };
    char squee_unit_separator[2] = { SQUEE_UNIT_SEPARATOR, '\0' };
    char squee_record_separator[2] = { SQUEE_RECORD_SEPARATOR, '\0' };
    char squee_end_of_text[2] =  { SQUEE_END_OF_TEXT, '\0' };
    size_t len;

    FILE *fd = fopen(file, "r");
    if (NULL == fd) {
        printf("Error opening file: %s \n", file);
        return(NULL);
    }

    Database *db = squee_new_empty_database();
    Header *curr_header = db->table->header;

    while(fgets(buffer, buffer_size, fd)) {
        tok = strsep(&pbuffer, squee_start_of_text);
        tok = strsep(&pbuffer, squee_unit_separator); 
        if (NULL == tok) {
            printf("squee_read_database_from_file() DB File ended prematurely. Aborting read. \n");
        }
        len = strlen(tok);
        db->table->name = (char*)malloc(len + 1);
        strncpy(db->table->name, tok, len);

        while(1) {
            type_s = strsep(&pbuffer, squee_record_separator);
            if (type_s[0] == SQUEE_END_OF_TEXT) {
                break;
            }
            else if (type_s[0] == '\0') {
                printf("Error reading file, premature end of file \n");
                return(NULL);
            }
            col = strsep(&type_s, squee_unit_separator);
            type = strtol(type_s, &endptr, 10);
            curr_header = squee_header_add_column(curr_header, col, type);
        }
    }

    fclose(fd);
    // Clean up all allocated memory except the db
    return db;
}

int squee_write_database_to_file(char *file, Database *db) {
    FILE *fd = fopen(file, "w");
    if (NULL == fd) {
        // TODO print errno
        printf("Error writing to [%s] \n", file);
        fclose(fd);
        return(1);
    }

    fprintf(fd, "SQUEE format 3%c", SQUEE_START_OF_TEXT);
    fprintf(fd, "%s%c",db->table->name, SQUEE_UNIT_SEPARATOR);

    // Write Header
    Header *hdr_p = db->table->header;
    while (NULL != hdr_p) {
        fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
        hdr_p = hdr_p->next;
    }

    // Write Row
#if 0
    if (NULL != db->table->row) {
        RowNode *row = db->table->row->next_row_node;
        // TODO FIXME THE NEXT LINE SEGFAULTS`
        while (SQUEE_TAIL != row->field_t) {
            switch(row->field_t) {
                case SQUEE_INT:
                    printf("squee_write_db(): INT Type [%i] Data [%i] \n", row->field_t, row->data.i);
                    break;
                case SQUEE_FLOAT:
                    printf("squee_write_db(): FLOAT Type [%i] Data [%f] \n", row->field_t, row->data.f);
                    break;
                case SQUEE_STRING:
                    printf("squee_write_db(): STRING Type [%i] Data [%s] \n", row->field_t, row->data.s);
                    break;
                case SQUEE_DATE:
                    printf("squee_write_db(): DATE Type [%i] Data [%i] \n", row->field_t, row->data.i);
                    break;
                case SQUEE_HEAD:
                    break;
                case SQUEE_TAIL:
                    break;
                default:
                    // printf("UK");
                    break;
            }
            row = row->next;
        }
    }
    else {
        printf("squee_write_db() not writing empty table \n");
    }
#endif

    fprintf(fd, "%c", SQUEE_END_OF_TEXT);
    fprintf(fd, "%c", SQUEE_END_OF_FILE);
    fclose(fd);
    return(0);
}

void squee_print_table(Table *tbl) {
    return;
    // RowNode *node = tbl->row->next_row_node;

    /*
    while (SQUEE_TAIL != node->field_t) {
        // print("squee_print_table() node->field_t [%i] \n", node->field_t);
        node = node->next;
    }
    */
}
