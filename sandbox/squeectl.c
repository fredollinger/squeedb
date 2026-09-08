#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "squee-structures.h"

void usage() {
    printf("usage: \n");
    printf("\n");
    printf("./squeectl");
    printf("\n");
}

void create_help() {
    printf("usage: \n");
    printf("\n");
    printf("./squeectl CREATE DATABASE filename.db");
    printf("\n");
    printf("./squeectl CREATE TABLE table_name filename.db");
    printf("\n");
}

/*
  CREATE TABLE table_name (
    column1 datatype constraint,
    column2 datatype constraint,
    column3 datatype constraint,
    ....
  ); filename.db
*/


int create_table(int argc, char* argv[]) {
    int len = (argc - 6) / 2;
    printf("CREATE_TABLE() [%i] [%s] len [%i] \n", argc, argv[argc - 1], len);

    if (0 != strcmp("(", argv[4])) {
        create_help();
        exit(1);
    }

    char **col_names = malloc(len * sizeof(char *));
    char **col_types = malloc(len * sizeof(char *));

    int c = 0;
    for (int i = 5; i < argc - 1; i = i + 2) {
        printf("create_table type [%s] [%s] \n", argv[i], argv[i + 1]);
        col_names[c] = strdup(argv[i]);
        col_types[c] = strdup(argv[i + 1]);
        c++;
    }

    // Database* squee_read_database_from_file(argv[argc]);
    // db->table = squee_new_table_with_header(argv[1], 2, (argc - 1) / 2, argv);
    return 0;
}

int create_database(char *filename) {
    printf("CREATE_DATABASE() [%s] \n", filename);
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
    printf("Creating New Something %s \n", argv[2]);
    if (0 == strcmp("SCHEMA", argv[2]) || 0 == strcmp("DATABASE", argv[2])) {
        exit(create_database(argv[3]));
    }
    else if (0 == strcmp("TABLE", argv[2])) {
        exit(create_table(argc, argv));
    }
    else {
        create_help();
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
        create(argc, argv);
    }
    else {
        usage();
        exit(0);
    }

    printf("squeectl filename [%s] \n", argv[argc - 1]);

    return(0);
}
