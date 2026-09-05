#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

/*
  CREATE TABLE table_name (
    column1 datatype constraint,
    column2 datatype constraint,
    column3 datatype constraint,
    ....
  ); 
*/

void usage() {
    printf("usage: \n");
    printf("\n");
    printf("./squeectl");
    printf("\n");
}

void create_help() {
    // TODO LIST CREATE COMMANDS
}

int create_database(char *filename) {
    printf("create_database() [%s] \n", filename);
    FILE *fd = fopen(filename, "w");
    if (NULL == fd) {
        printf("Error writing to %s \n", filename);
        return(1);
    }

    fprintf(fd, FILE_SIGNATURE);
    fclose(fd);
    return(0);
}

void create(int argc, char* argv[]) {
    if (0 == strcmp("SCHEMA", argv[2]) || strcmp("DATABASE", argv[2])) {
        exit(create_database(argv[2]));
    }
    else {
        usage();
        exit(-1);
    }
}

int main(int argc, char* argv[]) {
    printf("squeectl args [%i] \n", argc);
    if (1 >= argc) {
        usage();
        exit(0);
    }

    if (0 == strcmp("CREATE", argv[1])) {
        printf("Creating New Something \n");
    }
    else {
        usage();
        exit(0);
    }

    printf("squeectl filename [%s] \n", argv[argc - 1]);

    return(0);
}
