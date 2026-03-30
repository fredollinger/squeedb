#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new-table column1 column2 filename");
        printf("\n");
        return(0);
    }
    
/*
    int i;
    for(i = 0; i < argc - 1; i++) {
        printf("%i %s \n", i, argv[i]);
    }
*/

    Table *tbl = squee_new_table(0, argc - 1, argv);

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
