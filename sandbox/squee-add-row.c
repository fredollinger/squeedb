#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("usage: \n");
        printf("\n");
        printf("./[%s] table_name column1 column2 filename.db", argv[0]);
        printf("\n");
        return(0);
    }

    printf("Squee Add Row STUB \n");

    return(0);
}
