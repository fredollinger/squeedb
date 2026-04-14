#include <fcntl.h>
#include <stdio.h>
#include <string.h>
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

    FILE *fd = fopen(argv[argc - 1], "r");
    if (NULL == fd) {
        printf("%s: Error opening to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    Table *tbl = squee_new_empty_table();

    // TODO READ Table Name

    fclose(fd);

/*
    Table *tbl = squee_new_table(argv[1], 0, argc - 1, argv);
    printf("tbl->name [%s] \n", tbl->name);
    squee_print_header(tbl->header);

    FILE *fd = fopen(argv[argc - 1], "w");
    if (NULL == fd) {
        printf("%s: Error writing to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    fprintf(fd, "SQUEE format 3%c", SQUEE_START_OF_TEXT);

    Header *hdr_p = tbl->header;
    while (NULL != hdr_p) {
        if (hdr_p->field_t == SQUEE_INT) {
            printf("main(): Field Name: %s %i ", hdr_p->field_name, hdr_p->field_t);
            fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
            printf("\n");
        }
        hdr_p = hdr_p->next;
    }

    fprintf(fd, "%c", SQUEE_END_OF_TEXT);
    fprintf(fd, "%c", SQUEE_END_OF_FILE);

    fclose(fd);
*/

    return(0);
}
