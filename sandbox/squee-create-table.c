#include <fcntl.h>
#include <stdint.h>
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

    Database *db = squee_new_empty_database();
    db->table = squee_new_table_with_header(argv[1], 0, argc - 1, argv);

    squee_write_database_from_file(argv[argc - 1], db);

    // Table *tbl = squee_new_table_with_header(argv[1], 0, argc - 1, argv);

    /*
    FILE *fd = fopen(argv[argc - 1], "w");
    if (NULL == fd) {
        printf("%s: Error writing to %s \n", argv[0], argv[argc - 1]);
        return(1);
    }

    fprintf(fd, "SQUEE format 3%c", SQUEE_START_OF_TEXT);
    fprintf(fd, "%s%c",db->table->name, SQUEE_UNIT_SEPARATOR);

    Header *hdr_p = db->table->header;
    while (NULL != hdr_p) {
        fprintf(fd, "%s%c%i%c", hdr_p->field_name, SQUEE_UNIT_SEPARATOR, hdr_p->field_t, SQUEE_RECORD_SEPARATOR);
        hdr_p = hdr_p->next;
    }

    fprintf(fd, "%c", SQUEE_END_OF_TEXT);
    fprintf(fd, "%c", SQUEE_END_OF_FILE);
    fclose(fd);
    */

    return(0);
}
