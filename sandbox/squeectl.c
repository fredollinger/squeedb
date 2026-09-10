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
    printf("./squeectl CREATE TABLE Employees ('First Name' CHAR); filename.db");
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
    if (argc < 7) {
        printf("Syntax error: not enough arguments \n");
        create_help(); 
        exit(1);
    }
    int len = (argc - 6) / 2;
    printf("CREATE_TABLE() [%i] [%s] len [%i] \n", argc, argv[argc - 1], len);

    // Start parsing the arguments to CREATE TABLE
    // should be column_name, datatype
    int start = 4;
    // If the 1st argument is "(" then we need to skip it,
    // otherwise, they failed to put a space in between the 1st column name an "("
    // so we need to parse "(" out of the string
    if (0 == strcmp("(", argv[4])) {
        start = 5;
    }

    char **col_names = malloc(len * sizeof(char *));
    char **datatypes = malloc(len * sizeof(char *));

    int c = 0;
    printf("number of cols [%i] start [%i] \n", argc - 1, start);
    for (int i = start; i < argc - 1; i = i + 2) {
        // If they have put the ")" as a separate arg, we know we have reached the end
        // of the data.
        printf("cols [%s] [%s] \n", argv[i], argv[i + 1]);
        if (0 == strcmp(")", argv[i])) {
            printf("break on ) \n");
            break;
        }
        if (argv[i][0] == '(') {
            col_names[c] = strdup(argv[i] + 1);
            printf("starts with '(' [%s] \n", argv[i]);
        }
        else {
            col_names[c] = strdup(argv[i]);
        }
        printf("end [%c] \n" ,argv[i + 1][strlen(argv[i + 1]) - 1]);
        // The number of strings to cut, normally the whole length
        int cut = strlen(argv[i + 1]);
        // if there is a ')', we need to cut it out
        if (')' == argv[i + 1][strlen(argv[i + 1]) - 1]) {
            cut = strlen(argv[i + 1]) - 1;
            printf("ENDS WITH ')' [%s] [%i] \n", argv[i + 1], cut);
        }
        datatypes[c] = strndup(argv[i + 1], cut);
        printf("create_table type [%s] [%s] \n", col_names[c], datatypes[c]);

        c++;
    }

    printf("reading file [%s] \n", argv[argc - 1]);
    Database *db = squee_read_database_from_file(argv[argc - 1]);
    if (NULL == db) {
        printf("db is NULL \n");
        db = squee_new_empty_database();
    }
    db->table = squee_create_table(argv[3], c, col_names, datatypes);
    // squee_create_table(argv[3], c, col_names, datatypes);
    squee_write_database_to_file(argv[argc - 1], db);
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
