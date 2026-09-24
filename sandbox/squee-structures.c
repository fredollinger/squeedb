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

// 1 FKO FINISH AND TEST
Header* squee_create_header_with_columns(int num_cols, char* col_names[], char *datatypes[]) {
    Header *head = squee_new_empty_header();
    Header *curr = head;

    for (int i = 0; i < num_cols; i++) {
        // printf("squee_create_header_with_columns() [%s] [%s] \n", col_names[i], datatypes[i]);
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = strdup(col_names[i]);
        neu->field_t = squee_get_field_int(datatypes[i]);
        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;
    }
    return head;
}

Header* squee_new_header_with_columns(int begin, int end, char* cols[]) {
    Header *head = squee_new_empty_header();
    Header *curr = head;
    char *endptr;
    end = end * 2;
    int type;

    for (int i = begin; i < end; i = i + 2) {
        // printf("squee_new_header_with_columns() entry [%s] \n", cols[i]);
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[i]) + 1);
        neu->field_t = squee_get_field_int(cols[i + 1]);
        // printf("squee_new_header_with_columns type [%s] [%i] \n", cols[i + 1], neu->field_t);
        strcpy(neu->field_name, cols[i]);
        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;
    }
    return head;
}

// Table Methods
Table* squee_new_empty_table() {
    Table *head = (Table*) malloc(sizeof(Table));
    head->field_t = SQUEE_HEAD;
    head->row_id = -1;
    head->name = strdup("");

    Table *tail = (Table*) malloc(sizeof(Table));
    tail->field_t = SQUEE_TAIL;
    tail->row_id = -2;
    tail->name = strdup("");
    tail->next = NULL;
    head->next = tail;
    return head;
}

Table* squee_create_table(char *name, int num_cols, char* col_names[], char* datatypes[]) {
    Table *table = (Table*) malloc(sizeof(Table));
    table->name = strdup(name);
    table->header = squee_create_header_with_columns(num_cols, col_names, datatypes);
    table->field_t = SQUEE_DATA;
    table->row = squee_new_empty_row_list();
    return table;
}

// Need to actually add to the list not just replace it
// FKO TEST TO ENSURE THAT WE DO NOT HAVE DUPLICATE TABLES
// BEFORE APPENDING
bool squee_append_table(Database *db, Table *table) {
    Table *curr = db->table;
    Table *prev = db->table;
    while (SQUEE_TAIL != curr->field_t) {
        // check to ensure that we are not trying to insert two tables
        // with the same name
        printf("squee_append_table() table->field_t [%i] [%s] \n", table->field_t, table->name);
        printf("squee_append_table() curr->field_t [%i] [%s] \n", curr->field_t, curr->name);
        if (0 == strcmp(table->name, curr->name)) {
            printf("duplicate entry!! \n");
            return false;
        }
        prev = curr;
        curr = curr->next;
    }
    // printf("CURR [%s] \n", curr->name);
    // printf("TAIL [%i] \n", curr->next->field_t);
    // insert the table
    table->next = curr; // curr is now the tail
    prev->next = table;
    return true;
}

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

// Row Methods

// there's a bug here, check chat gpt logs
RowNode* squee_create_row(Header *header, char* cols[], int len) {
    Header *hdr_p = header;

    RowNode *curr = (RowNode*)malloc(sizeof(RowNode));
    curr->field_t = SQUEE_HEAD;
    curr->next = NULL;
    RowNode *head = curr;

    long value; // used for string conversion
    float fvalue; // used for string conversion
    char *endptr;

    // Skip over header
    if (hdr_p->field_t == SQUEE_HEAD) {
        hdr_p = hdr_p->next;
    }

    int i = 0;
    for(int i = 0; i < len; i++) {
        RowNode *neu = (RowNode*)malloc(sizeof(RowNode));
        neu->field_t = hdr_p->field_t;

        // TODO copy col data into the Row
        switch(hdr_p->field_t) {
            case SQUEE_INT:
                value = strtol(cols[i], &endptr, 10);
                neu->data.i = (int)value;
                break;
            case SQUEE_FLOAT:
                fvalue = strtof(cols[i], &endptr);
                neu->data.f = fvalue;
                break;
            case SQUEE_STRING:
                neu->data.s = strdup(cols[i]);
                break;
            case SQUEE_DATE:
                break;
            case SQUEE_HEAD:
                break;
            case SQUEE_TAIL:
                break;
            default:
                printf("squee_create_row() UNKNOWN DEFAULT [%s] \n", cols[i]);
                break;
        }
        curr->next = neu;
        curr = neu;
        hdr_p = hdr_p->next;
    }

    RowNode *tail = (RowNode*)malloc(sizeof(RowNode));
    tail->field_t = SQUEE_TAIL;
    curr->next = tail;
    return head;
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

Table* squee_get_table_by_name(char *table_name, Database *db) {
    Table *curr = db->table;
    printf("squee_get_table_by_name() [%u] \n", curr->field_t);

    // FKO THIS IS THE BUG
    while (SQUEE_TAIL != curr->field_t) {
        printf("squee_get_table_by_name [%i] [%s] \n", curr->field_t, curr->name);
        if (0 == strcmp(table_name, curr->name)) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// TODO NOT DONE FKO
// Take a new row and add it to the linked list
Row* squee_append_row(char *table_name, Database *db, Row *row) {
    Table *table = squee_get_table_by_name(table_name, db);
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

// Database Methods

Database* squee_new_empty_database() {
    Database *db = (Database*) malloc(sizeof(Database));
    db->table = squee_new_empty_table();
    return db;
}

// Print Methods

// FKO TODO NOT DONE
void squee_print_table(Table *table) {
    Table *curr = table;
    printf("\n");
    while (SQUEE_TAIL != curr->field_t) {
    /*
       printf(
            "curr=%p name=%p [%s] type=%i row_id=%i next=%p\n",
            (void *)curr,
            (void *)curr->name,
            curr->name,
            curr->field_t,
            curr->row_id,
            (void *)curr->next
        );
    */
        printf("print_table() TABLE name [%s] type [%i] row id [%i] \n", curr->name, curr->field_t, curr->row_id);
        curr = curr->next;
    }
    printf("print_table() TAIL [%i] \n\n", curr->field_t);
    return;
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

void squee_print_Table(Table *tbl) {
    Table *tbl_p = tbl;
}

// IO
// TODO NEED TO POPULATE THIS
int squee_write_table_to_file(Table *table, FILE *fd) {
    return 0;
}

void squee_write_header_to_file(Header *header, char *name, FILE *fd) {
    fprintf(fd, "SQUEE format 3%c", SQUEE_START_HEADER);

    fprintf(fd, "%s%c", name, SQUEE_UNIT_SEPARATOR);

    // Write Header
    Header *hdr_p = header;
    while (NULL != hdr_p) {
        if (NULL == hdr_p->field_name) {
            hdr_p = hdr_p->next;
            continue;
        }
        fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
        hdr_p = hdr_p->next;
    }
    fprintf(fd, "%c", SQUEE_END_HEADER);
    return;
}

int squee_write_database_to_file(char *file, Database *db) {
    FILE *fd = fopen(file, "w");
    if (NULL == fd) {
        printf("Error writing to [%s] errono [%i] \n", file, errno);
        fclose(fd);
        return(1);
    }

    // TODO loop through the headers
    squee_write_header_to_file(db->table->next->header, db->table->next->name, fd);

    // Write Row
    fprintf(fd, "%c", SQUEE_START_ROW);
    // FKO TODO NEED TO LOOP THROUGH TABLE
    // FOR NOW, WE WRITE THE 1st Table only
    Row *curr = db->table->next->row;
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

Header* squee_read_header_from_file (char **buffer, char **pbuffer) {
    Header *header = squee_new_empty_header();
    // FKO TODO REMOVE
    // ALSO need to return NULL if there is no header

    // Read Header
    while (*pbuffer != SQUEE_END_HEADER) {
        /*
        // Read field name
        char *start = pbuffer;
    
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
        */
        pbuffer++;      // Skip RECORD_SEPARATOR
    }
    return header;
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
    char *pbuffer = NULL;

    FILE *fd = fopen(file, "rb");
    Database *db = squee_new_empty_database();

    if (NULL == fd) {
        return(db);
    }

    // TODO, we need to read ahead to even see if we need a header
    // Header *header = db->table->header;

    fseek(fd, 0, SEEK_END);
    long filesize = ftell(fd);
    rewind(fd);

    buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        fclose(fd);
        return(db);
    }

    fread(buffer, 1, filesize, fd);
    buffer[filesize] = '\0';
    fclose(fd);

    pbuffer = buffer;
    const char *magic = "SQUEE format 3";
    size_t magic_len = strlen(magic);
    
    if (strncmp(pbuffer, magic, magic_len) != 0) {
        free(buffer);
        return(db);
    }

    char *start = pbuffer;
    while (*pbuffer != SQUEE_UNIT_SEPARATOR)
        pbuffer++;
    len = pbuffer - start;

    Table *table = (Table*) malloc(sizeof(Table));
    table->name = (char*)malloc(len + 1);
    strncpy(table->name, start, len);
    pbuffer++;      // Skip UNIT_SEPARATOR

    // Read header from file
    Header *header = squee_read_header_from_file (&buffer, &pbuffer);

    // Read Table Name
    pbuffer += magic_len;

    // Read Row
    while (SQUEE_END_ROW != *(pbuffer + 1)) {
        if (SQUEE_RECORD_SEPARATOR == *pbuffer) {
            // break;
        }
        Header *hdr_p = header;
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
      squee_append_row(table->name, db, row);
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
