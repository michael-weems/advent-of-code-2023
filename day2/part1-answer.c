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

int RED = 12;
int GREEN = 13;
int BLUE = 14;

int parseCount(char * line, int * cursor, size_t len) {
    char blocks[2] = "";
    int blockIndex = 0;

    while (line[*cursor] != ' ') {
        blocks[blockIndex++] = line[(*cursor)++];
    }
    blocks[blockIndex] = '\0';

    *cursor = *cursor + 1;
    int ret =  atoi(blocks);
    printf("parsedBlocks %s - %d\n", blocks, ret);
    return ret;
}

void advance(char * line, int * cursor, size_t len) {
    while(*cursor < len  ) {
        if (line[*cursor] == ',' || line[*cursor] == ';') {
            *cursor = *cursor + 2;
            return;
        }

        *cursor = *cursor + 1;
    }
}

int validGame(char * line, int * cursor, size_t len){
    printf("validGame len: %zu - %s", len, line);
    printf("char at %d: %c\n", *cursor, line[*cursor]);

    while (len > *cursor) {
        int blocks = parseCount(line, cursor, len);
        // printf("blocks: %d\n", blocks);

        if (line[*cursor] == 'r' && blocks > RED) {
            printf("INVALID GAME!! RED blocks: %d\n", blocks);
            return 0;
        }

        if (line[*cursor] == 'b' && blocks > BLUE) {
            printf("INVALID GAME!! BLUE blocks: %d\n", blocks);
            return 0;
        }

        if (line[*cursor] == 'g' && blocks > GREEN) {
            printf("INVALID GAME!! GREEN blocks: %d\n", blocks);
            return 0;
        }

//        printf("cursor position %d", *cursor);
        advance(line, cursor, len);
//        printf(" --> advanced to %d\n", *cursor);

    }

    return 1;
}

int gameId(char * line, int * cursor){
    // printf("gameId %s\n", line);

    char id[3] = "";
    int idIndex = 0;
    while(line[*cursor] != ':') {
        // printf("char at %d: %c\n", *cursor, line[*cursor]);
        id[idIndex++] = line[(*cursor)++];
    }
    *cursor = *cursor + 2;

    // printf("id: %s\n", id);
    int idInt = atoi(id);
    // printf("int id: %d\n", idInt);
    return idInt;
}


int main(void){

    FILE * fp = openFile("./input");

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    int sum = 0;
    while ((read = getline(&line, &len, fp)) != -1) {

        int cursorValue = 5;
        int *cursor = &cursorValue;

        int id = gameId(line, cursor);

        size_t length = strlen(line);
        if (validGame(line, cursor, length)) {
            printf("SUCCESSFUL GAME: %d\n", id);
            sum = sum + id;
        }
        printf("--------------------------------------------------------------\n");
    }

    printf("sum %d\n", sum);

    closeFile(fp, line);
    exit(EXIT_SUCCESS);
}
