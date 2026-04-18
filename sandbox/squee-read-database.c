#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("Read database into memory \n");
        printf("Usage \n\n");
        printf("./squee-read-database filename.db");
        printf("\n");
        return(0);
    }

    int buffer_size = 10000;
    char buffer[buffer_size];
    char *pbuffer = buffer;
    char *tok, *col, *type;
    char squee_start_of_text[2] = { SQUEE_START_OF_TEXT, '\0' };
    char squee_unit_separator[2] = { SQUEE_UNIT_SEPARATOR, '\0' };
    char squee_record_separator[2] = { SQUEE_RECORD_SEPARATOR, '\0' };
    char squee_end_of_text[2] =  { SQUEE_END_OF_TEXT, '\0' };
    size_t len;

    printf("opening file %s \n", argv[argc - 1]);

    FILE *fd = fopen(argv[argc - 1], "r");
    if (NULL == fd) {
        printf("%s: Error opening to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    Table *tbl = squee_new_empty_table();

    while(fgets(buffer, buffer_size, fd)) {
        printf("%s", buffer);
        tok = strsep(&pbuffer, squee_start_of_text);
        printf("start of string [%s] \n", tok);
        tok = strsep(&pbuffer, squee_unit_separator); 
        len = strlen(tok);
        tbl->name = (char*)malloc(len + 1);
        strncpy(tbl->name, tok, len);
        printf("table name [%s] \n", tbl->name);
        type = strsep(&pbuffer, squee_record_separator);
        col = strsep(&type, squee_unit_separator);
        printf("column [%s] [%s] \n", col, type);
/*
        Header *head = squee_new_empty_header();
        Header *curr = head;
        tbl->header = head;
        while(NULL != tok) {
            printf("column [%s] \n", tok);
            //curr = squee_header_add_column(); // todo need to get field_t
            tok = strsep(&pbuffer, squee_record_separator);
            tok = strsep(&pbuffer, squee_unit_separator);
        }
*/
    }

    fclose(fd);

    return(0);
}
