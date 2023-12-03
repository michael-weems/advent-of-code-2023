#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE * openFile(char filename[]){
    FILE * fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    return fp;
}

void closeFile(FILE * fp, char * line){
    fclose(fp);
    if (line) {
        free(line);
    }
}

int main(void){

    FILE * fp = openFile("./test");
    //FILE * fp = openFile("./input");

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    char * prev = NULL;
    char * next = NULL;


    int total = 0;

    read = getline(&line, &len, fp);

    size_t line_length = strlen(line);

    char *pointer;
    int c;
    int length = 3;
    pointer = malloc(length + 1);
    if (pointer == NULL) {
        exit(EXIT_FAILURE);
    }

    for (c = 0; c < length; c++) {
        *(pointer + c) = *((line + 0) + c);
        printf("%d %c\n", c, *(pointer + c));
    }

    //*(pointer + c + 1) = '\0';
    printf("\n");
    printf("pointer[0] %c\n", pointer[0]);
    printf("pointer[1] %c\n", pointer[1]);
    printf("pointer[2] %c\n", pointer[2]);
    printf("pointer[3] %c\n", pointer[3]);
    printf("one by one: \"%c%c%c%c\"\n", pointer[0], pointer[1], pointer[2], pointer[3]);

    char *end;
    printf("substring result: %ld\n", strtol(pointer, &end, 10));
    long int result = strtol(pointer, &end, 10);

    printf("---------------------------------------------------------\n\n");
    printf("result %zu\n", result);

    closeFile(fp, line);
    exit(EXIT_SUCCESS);
}
