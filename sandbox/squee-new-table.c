#include <stdio.h>
#include <fcntl.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./squee-new column1 column2 filename");
        printf("\n");
        return(0);
    }
    
    squee_new_table(0, argc - 2, argv);

    // 1. check to see if the file exists, if it does not then error out 

    // 2. need to open with new flags, open as append
    open(argv[argc - 1], O_WRONLY, O_APPEND, O_SYMLINK);

    return(0);
}
