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

    FILE *fd = fopen(argv[argc - 1], "r");
    if (NULL == fd) {
        printf("%s: Error opening to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    Database *db = squee_new_empty_database();
    db->table->header = squee_new_empty_header();
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
            }
            col = strsep(&type_s, squee_unit_separator);
            type = strtol(type_s, &endptr, 10);
            curr_header = squee_header_add_column(curr_header, col, type);
        }
    }

    fclose(fd);

    squee_print_header(db->table->header);

    return(0);
}
