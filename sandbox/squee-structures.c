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

    for (int i = begin; i < end; i = i + 2) {
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[1]) + 1);
        type = strtol(cols[i + 1], &endptr, 10);
        neu->field_t = type;
        strcpy(neu->field_name, cols[i]);
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

Table* squee_new_table_with_header(char *name, int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    size_t name_len = strlen(name);
    tbl->name = (char*)malloc(name_len + 1);
    strncpy(tbl->name, name, name_len);
    tbl->header = squee_new_header_with_columns(begin + 2, end, cols);
    tbl->row = NULL;
    return tbl;
}

// ROW METHODS
/*
Row* squee_new_empty_row() {
    Row *row = (Row*)malloc(sizeof(Row));
    return row;
}
*/

Row* squee_add_row(Table *table, char* cols[], int len) {
    Header *header_p = table->header->next->next;
    char *endptr; // used for string conversion
    long value; // used for string conversion

    Row *row_h = (Row*)malloc(sizeof(Row));
    RowNode *row = (RowNode*)malloc(sizeof(RowNode));
    row_h->field_t = SQUEE_HEAD;
    row_h->next_row_node = row;
    RowNode *last = row;

    for (int i = 0; i < len; i++) {
        printf("squee_add_row() Header [%s] Type [%i] Item [%s] \n", header_p->field_name, header_p->field_t, cols[i]);
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

    row = (RowNode*)malloc(sizeof(RowNode));
    row->field_t = SQUEE_TAIL;
    last->next = row;
    return row_h;
}

void squee_print_row(Row *row_h) {
    RowNode *row = row_h->next_row_node;

    while (SQUEE_TAIL != row->field_t) {
        switch(row->field_t) {
            case SQUEE_INT:
                printf("squee_print_row(): INT Type [%i] Data [%i] \n", row->field_t, row->data.i);
                break;
            case SQUEE_FLOAT:
                printf("squee_print_row(): FLOAT Type [%i] Data [%f] \n", row->field_t, row->data.f);
                break;
            case SQUEE_STRING:
                printf("squee_print_row(): STRING Type [%i] Data [%s] \n", row->field_t, row->data.s);
                break;
            case SQUEE_DATE:
                printf("squee_print_row(): DATE Type [%i] Data [%i] \n", row->field_t, row->data.i);
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

    printf("squee_print_row(): Type [%i] \n", row->field_t);
}

// Given the field type print a header
void squee_print_field_type(Header *hdr) {
    switch(hdr->field_t){
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
            squee_print_field_type(hdr_p);
            printf("\n");
        }
        hdr_p = hdr_p->next;
    }
}

Database* squee_new_empty_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    db->table = squee_new_empty_table();
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
    if (NULL != db->table->row) {
        RowNode *row = db->table->row->next_row_node;
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
