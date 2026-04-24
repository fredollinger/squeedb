#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new-table table_name column1 column2 filename.db");
        printf("\n");
        return(0);
    }

    Table *tbl = squee_new_table_with_header(argv[1], 0, argc - 1, argv);
    printf("tbl->name [%s] \n", tbl->name);
    squee_print_header(tbl->header);

    FILE *fd = fopen(argv[argc - 1], "w");
    if (NULL == fd) {
        printf("%s: Error writing to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    fprintf(fd, "SQUEE format 3%c", SQUEE_START_OF_TEXT);
    fprintf(fd, "%s%c",tbl->name, SQUEE_UNIT_SEPARATOR);

    Header *hdr_p = tbl->header;
    while (NULL != hdr_p) {
        printf("\n main(): Field Name: %s %i ", hdr_p->field_name, hdr_p->field_t);
        fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
        printf("\n");
        hdr_p = hdr_p->next;
    }

    fprintf(fd, "%c", SQUEE_END_OF_TEXT);
    fprintf(fd, "%c", SQUEE_END_OF_FILE);

    fclose(fd);

    return(0);
}
