#include <assert.h>
#include <errno.h>
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

int squee_get_field_int(char *type) {
    if (0 == strcmp("INT", type)) {
        return SQUEE_INT;
    }
    else if (0 == strcmp("FLOAT", type)) {
        return SQUEE_FLOAT;
    }
    else if (0 == strcmp("CHAR", type)) {
        return SQUEE_STRING;
    }
    else if (0 == strcmp("DATE", type)) {
        return SQUEE_DATE;
    }
    return -1;
}

Header* squee_new_header_with_columns(int begin, int end, char* cols[]) {
    Header *head = squee_new_empty_header();
    Header *curr = head;
    char *endptr;
    end = end * 2;
    int type;

    for (int i = begin; i < end; i = i + 2) {
        printf("squee_new_header_with_columns() entry [%s] \n", cols[i]);
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[i]) + 1);
        // type = strtol(cols[i + 1], &endptr, 10);
        // neu->field_t = type;
        neu->field_t = squee_get_field_int(cols[i + 1]);
        printf("squee_new_header_with_columns type [%s] [%i] \n", cols[i + 1], neu->field_t);
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

// TODO FKO FIXME THIS IS BROKEN
Table* squee_new_table_with_header(char *name, int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    size_t name_len = strlen(name);
    tbl->name = (char*)malloc(name_len + 1);
    strncpy(tbl->name, name, name_len);
    tbl->header = squee_new_header_with_columns(begin, end, cols);

    tbl->row = squee_new_empty_row_list();
    return tbl;
}

// ROW METHODS

Row* squee_create_row(Header *hdr_p, char* cols[], int len) {
    Row *row = (Row*)malloc(sizeof(Row));
    row->field_t = SQUEE_DATA;
    row->id = -1;

    RowNode *curr = (RowNode*)malloc(sizeof(RowNode));
    curr->field_t = SQUEE_HEAD;
    row->next_row_node = curr;

    long value; // used for string conversion
    float fvalue; // used for string conversion
    char *endptr;

    int i = 0;
    while (NULL != hdr_p) {
        if (SQUEE_HEAD == hdr_p->field_t) {
            hdr_p = hdr_p->next;
            continue;
        }

        RowNode *neu = (RowNode*)malloc(sizeof(RowNode));
        neu->field_t = hdr_p->field_t;

        // TODO copy col data into the Row
        switch(neu->field_t) {
            case SQUEE_INT:
                value = strtol(cols[i], &endptr, 10);
                neu->data.i = (int)value;
                break;
            case SQUEE_FLOAT:
                fvalue = strtof(cols[i], &endptr);
                neu->data.f = fvalue;
                // printf("squee_create_row FLOAT [%s] [%s] [%f] \n", cols[i], endptr, neu->data.f);
                break;
            case SQUEE_STRING:
                neu->data.s = strdup(cols[i]);
                // neu->data.s = (char*)malloc(strlen(cols[i]));
                // strcpy(neu->data.s, cols[i]);
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

        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;

        i = i + 1;
        hdr_p = hdr_p->next;

    }

    RowNode *tail = (RowNode*)malloc(sizeof(RowNode));
    tail->field_t = SQUEE_TAIL;
    curr->next = tail;

    return row;
}

RowNode* squee_new_empty_row_node_list() {
    RowNode *tail_row = (RowNode*) malloc(sizeof(RowNode));
    tail_row->field_t = SQUEE_TAIL;
    RowNode *head_row = (RowNode*) malloc(sizeof(RowNode));
    head_row->field_t = SQUEE_HEAD;
    head_row->next = tail_row;
    return head_row;
}

Row* squee_new_empty_row_list() {

    // Create empty row list
    Row *tail_row = (Row*) malloc(sizeof(Row));
    tail_row->field_t = SQUEE_TAIL;
    tail_row->next_row_node = NULL;

    Row *head_row = (Row*) malloc(sizeof(Row));
    head_row->field_t = SQUEE_HEAD;
    head_row->next_row_node = NULL;
    head_row->next = tail_row;

    return head_row;

}

// TODO NOT DONE FKO
// Take a new row and add it to the linked list
Row* squee_append_row(Table *table, Row *row) {
    Row *prev = table->row;
    while (SQUEE_TAIL != prev->next->field_t) {
        prev = prev->next;
    }
    Row *last = prev->next;
    prev->next = row;
    row->next = last;
    table->row_id = table->row_id + 1;
    row->id = table->row_id;
    return row;
}

// Print Methods

// FKO TODO NOT DONE
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

void squee_print_delimiter(int c) {
    switch(c) {
        case SQUEE_UNIT_SEPARATOR:
            printf("SQUEE_UNIT_SEPARATOR");
            break;
        case SQUEE_RECORD_SEPARATOR:
            printf("SQUEE_RECORD_SEPARATOR");
            break;
        case SQUEE_START_HEADER:
            printf("SQUEE_START_HEADER");
            break;
        case SQUEE_END_HEADER:
            printf("SQUEE_END_HEADER");
            break;
        case SQUEE_START_ROW:
            printf("SQUEE_START_ROW");
            break;
        case SQUEE_END_ROW:
            printf("SQUEE_END_ROW");
            break;
        case SQUEE_END_FILE:
            printf("SQUEE_END_ROW");
            break;
        default:
            printf("UK");
            break;
    }
}



void squee_print_row_node(RowNode *node) {
    if (NULL == node) return;
    RowNode *curr = node;
    switch(curr->field_t) {
        case SQUEE_INT:
            printf("squee_print_row_node(): INT Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
            break;
        case SQUEE_FLOAT:
            printf("squee_print_row_node(): FLOAT Type [%i] Data [%f] \n", curr->field_t, curr->data.f);
            break;
        case SQUEE_STRING:
            printf("squee_print_row_node(): STRING Type [%i] Data [%s] \n", curr->field_t, curr->data.s);
            break;
        case SQUEE_DATE:
            printf("squee_print_row_node(): DATE Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
            break;
        case SQUEE_HEAD:
            printf("squee_print_row_node(): HEAD Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
            break;
        case SQUEE_TAIL:
            printf("squee_print_row_node(): TAIL Type [%i] Data [%i] \n", curr->field_t, curr->data.i);
            break;
        default:
            break;
    }
}

// Given a row, find the last element (before the tail)
// DELETE ME
RowNode* squee_end_of_row(Row *row_h) {
    return NULL;
}

// print all a single row
void squee_print_row(Row *row) {
    RowNode *node = row->next_row_node;
    if (NULL == node) return;
    int c = 0;
    while (SQUEE_TAIL != node->field_t) {
        printf("%i: ", c);
        squee_print_row_node(node);
        node = node->next;
        c = c + 1;
    }
    printf("%i: ", c++);
    squee_print_row_node(node);
}

// print a all rows
void squee_print_rows(Row *row) {
    printf("print_rows() BEGIN \n");
    Row *curr = row;
    if (NULL == row) return;
    while (SQUEE_TAIL != curr->field_t) {

        printf("print_rows() id [%i] type [", curr->id);
        squee_print_field_type(curr->field_t);
        printf("] \n");

        squee_print_row(curr);
        curr = curr->next;
    }

    printf("print_rows() id [%i] type [", curr->id);
    squee_print_field_type(curr->field_t);
    printf("] \n");
    printf("print_rows() END \n");
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
            printf("SQUEE_HEAD");
            break;
        case SQUEE_TAIL:
            printf("SQUEE_TAIL");
            break;
        case SQUEE_DATA:
            printf("SQUEE_DATA");
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
    db->table->row = squee_new_empty_row_list();

    return db;
}

void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}

// IO

int squee_write_database_to_file(char *file, Database *db) {
    FILE *fd = fopen(file, "w");
    if (NULL == fd) {
        printf("Error writing to [%s] errono [%i] \n", file, errno);
        fclose(fd);
        return(1);
    }

    fprintf(fd, "SQUEE format 3%c", SQUEE_START_HEADER);
    fprintf(fd, "%s%c",db->table->name, SQUEE_UNIT_SEPARATOR);

    // Write Header
    Header *hdr_p = db->table->header;
    while (NULL != hdr_p) {
        if (NULL == hdr_p->field_name) {
            hdr_p = hdr_p->next;
            continue;
        }
        fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
        hdr_p = hdr_p->next;
    }
    fprintf(fd, "%c", SQUEE_END_HEADER);

    // Write Row
    fprintf(fd, "%c", SQUEE_START_ROW);
    Row *curr = db->table->row;
    while (SQUEE_TAIL != curr->field_t) {
        if (SQUEE_HEAD == curr->field_t) {
            curr = curr->next;
            continue;
        }

        RowNode *node = curr->next_row_node;
        while (SQUEE_TAIL != node->field_t) {
            switch(node->field_t) {
                case SQUEE_INT:
                    fprintf(fd, "%i%c", node->data.i, SQUEE_UNIT_SEPARATOR);
                    break;
                case SQUEE_FLOAT:
                    fprintf(fd, "%f%c", node->data.f, SQUEE_UNIT_SEPARATOR);
                    break;
                case SQUEE_STRING:
                    fprintf(fd, "%s%c", node->data.s, SQUEE_UNIT_SEPARATOR);
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
            node = node->next;
        }
        fprintf(fd, "%c", SQUEE_RECORD_SEPARATOR);
        curr = curr->next;
    }

    fprintf(fd, "%c", SQUEE_END_ROW);
    fprintf(fd, "%c", SQUEE_END_FILE);
    fclose(fd);
    return(0);
}

Database* squee_read_database_from_file(char *file) {
    int type = 0;
    char *endptr = NULL;
    char *buffer;
    char *tok, *col, *type_s, *prev;
    char squee_start_of_header[2] = { SQUEE_START_HEADER, '\0' };
    char squee_unit_separator[2] = { SQUEE_UNIT_SEPARATOR, '\0' };
    char squee_record_separator[2] = { SQUEE_RECORD_SEPARATOR, '\0' };
    char squee_end_of_header[2] =  { SQUEE_END_HEADER, '\0' };
    char squee_start_of_row[2] = { SQUEE_START_ROW, '\0' };
    char squee_end_of_row[2] = { SQUEE_END_ROW, '\0' };
    size_t len;
    char value_str[256];
    // char *endptr;

    FILE *fd = fopen(file, "rb");
    Database *db = squee_new_empty_database();

    if (NULL == fd) {
        return(db);
    }

    Header *header = db->table->header;

    fseek(fd, 0, SEEK_END);
    long filesize = ftell(fd);
    rewind(fd);

    buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        fclose(fd);
        return NULL;
    }

    fread(buffer, 1, filesize, fd);
    buffer[filesize] = '\0';
    fclose(fd);

    char *pbuffer = buffer;

    const char *magic = "SQUEE format 3";
    size_t magic_len = strlen(magic);
    
    if (strncmp(pbuffer, magic, magic_len) != 0) {
        free(buffer);
        return NULL;
    }

    // Read Table Name
    pbuffer += magic_len;
    char *start = pbuffer;
    while (*pbuffer != SQUEE_UNIT_SEPARATOR)
        pbuffer++;
    len = pbuffer - start;
    db->table->name = (char*)malloc(len + 1);
    strncpy(db->table->name, start, len);
    
    pbuffer++;      // Skip UNIT_SEPARATOR

    // Read Header
    while (*pbuffer != SQUEE_END_HEADER) {
    
        // Read field name
        start = pbuffer;
    
        while (*pbuffer != SQUEE_UNIT_SEPARATOR)
            pbuffer++;
    
        len = pbuffer - start;
        char field_name[256];
        memcpy(field_name, start, len);
        field_name[len] = '\0';

        pbuffer++;      // Skip SQUEE_UNIT_SEPARATOR

        start = pbuffer;
        while (*pbuffer != SQUEE_RECORD_SEPARATOR)
            pbuffer++;
 
        len = pbuffer - start;
    
        char type_str[16];
        memcpy(type_str, start, len);
        type_str[len] = '\0';
        int field_type = atoi(type_str);

        header = squee_header_add_column(header, field_name, field_type);
   
        // Last line
        pbuffer++;      // Skip RECORD_SEPARATOR
    }

    // Read Row
    while (SQUEE_END_ROW != *(pbuffer + 1)) {
        if (SQUEE_RECORD_SEPARATOR == *pbuffer) {
            // break;
        }
        Header *hdr_p = db->table->header;
        Row *row = (Row*)malloc(sizeof(Row*));
        row->next_row_node = squee_new_empty_row_node_list();

        while (SQUEE_TAIL != hdr_p->field_t) {
            // Skip Header
            if (SQUEE_HEAD == hdr_p->field_t) {
                hdr_p = hdr_p->next;
                continue;
            }
    
            start = pbuffer;
            // END OF FILE [3] [4] [5] [6] 
            while (*pbuffer != SQUEE_UNIT_SEPARATOR) {
                if (SQUEE_END_FILE == *pbuffer) return db;
                pbuffer++;
            }
    
            len = pbuffer - start;
            RowNode *node = (RowNode*)malloc(sizeof(RowNode));
            memcpy(value_str, start, len);
            value_str[len] = '\0';

            switch(hdr_p->field_t) {
                case SQUEE_INT:
                    node->field_t = SQUEE_INT;
                    node->data.i = (int)strtol(value_str, NULL, 10);
                    break;
                case SQUEE_FLOAT:
                    node->field_t = SQUEE_FLOAT;
                    node->data.f = strtof(value_str, NULL);
                    break;
                case SQUEE_STRING:
                    node->data.s = (char*)malloc(len + 1);
                    memcpy(node->data.s, start, len);
                    node->field_t = SQUEE_STRING;
                    break;
                case SQUEE_DATE:
                case SQUEE_HEAD:
                case SQUEE_TAIL:
                default:
                    break;
            }
            squee_append_row_node(row, node);
            pbuffer++;      // Skip SQUEE_UNIT_SEPARATOR
            hdr_p = hdr_p->next;
      } // END Row Node Loop
      squee_append_row(db->table, row);
      squee_print_row(row);
    } // END Row Loop
    return db;
}
 
void squee_append_row_node(Row *row, RowNode *node) {
    RowNode *prev = row->next_row_node;
    while (SQUEE_TAIL != prev->next->field_t) {
        prev = prev->next;
    }
    RowNode *last = prev->next;
    prev->next = node;
    node->next = last;
    return;
}
