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

    Table *tbl = squee_new_table(argv[1], 0, argc - 1, argv);
    Header *hdr_p = tbl->header;

    while (NULL != hdr_p) {
        if (hdr_p->field_t == INT) {
            printf("main(): Field Name: %s \n", hdr_p->field_name);
        }
        hdr_p = hdr_p->next;
    }

    // 1. check to see if the file exists, if it does not then error out 

    // 2. need to open with new flags, open as append
    /*
    int fd = open(argv[argc - 1], O_WRONLY, O_APPEND, O_SYMLINK);
    if (-1 == fd) {
        printf("./squee-new-table Can't open file %s \n", argv[argc - 1]);
    }

    write(fd, argv[1], strlen(argv[1]));
    */

    return(0);
}
