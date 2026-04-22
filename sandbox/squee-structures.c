#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "squee-structures.h"

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

Header* squee_new_header(int begin, int end, char* cols[]) {
    Header *head = squee_new_empty_header();
    Header *curr = head;
    for (int i = begin; i < end; i++) {
        Header *neu = (Header*)malloc(sizeof(Header));
        neu->field_name = (char*)malloc(strlen(cols[1]) + 1);
        // TODO Once we get a real parser, we won't just assume that this is INT
        neu->field_t = SQUEE_INT;
        strcpy(neu->field_name, cols[i]);
        curr->next = neu;
        neu->next = curr->next->next;
        curr = neu;
    }
    return head;
}

Table* squee_new_empty_table() {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    return tbl;
}

Table* squee_new_table(char *name, int begin, int end, char* cols[]) {
    int i;
    Table *tbl = (Table*) malloc(sizeof(Table));
    size_t name_len = strlen(name);
    tbl->name = (char*)malloc(name_len + 1);
    strncpy(tbl->name, name, name_len);
    tbl->header = squee_new_header(begin + 2, end, cols);
    return tbl;
}

// Given the field type print a header
void squee_print_field_type(Header *hdr) {
    printf("current field %i SQUEE_INT %i ", hdr->field_t, SQUEE_INT);
    switch(hdr->field_t){
        case SQUEE_INT:
            printf("INT");
            break;
        default:
            printf("UK");
            break;
    }
}

void squee_print_header(Header *hdr) {
    Header *hdr_p = hdr;
    while (NULL != hdr_p) {
        if (hdr_p->field_t == SQUEE_INT) {
            printf("Field Name: %s Field Type: %i ", hdr_p->field_name, hdr_p->field_t);
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

Database* squee_read_database_from_file(char *file) {
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

