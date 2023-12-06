#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void green(void) {
    printf("\033[0;32m");
}
void red(void) {
    printf("\033[0;31m");
}
void reset(void) {
    printf("\033[0m");
}


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

int substring(char *string, int position, int length){
    char *pointer;
    int c;

    pointer = malloc(length + 2);
    if (pointer == NULL) {
        exit(EXIT_FAILURE);
    }

    for (c = 0; c < length; c++) {
        *(pointer + c) = *((string + position) + c);
    }

    *(pointer + c + 1) = '\0';

    char *end = "\0";
    int result = strtol(pointer, &end, 10);
    return result;
}

void trimNewline(char * line) {
    int length = strlen(line);
    if (line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }
}

int extractNumber(char * line, int *cursor){
    int s = *cursor;
    int e = *cursor;
    if (line[*cursor] == ' '){
        (*cursor)++;
    }
    while (1 == isdigit(line[*cursor])){
           e = *cursor;
            (*cursor)++;
            if (0 == isdigit(line[*cursor])){
                int number = substring(line, s, e + 1 - s);
                (*cursor)++;
                return number;
            }
    }
    return 0;
}

int cardPoints(int argc, char* argv[]) {
    printf("---------------------------------------------------------\n\n");

    if (argc == 1) {
        printf("Running default program, no inputs provided\n");
    }

    if (argc >= 2) {
        printf("Number Of Arguments Passed: %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }

    char * filename = "./input\0";
    if (argc >= 2) {
        filename = argv[1];
        printf("Using file: %s\n", filename);
    }

    int debug_line_number = -1;
    if (argc >= 3) {
        char *ptr;
        debug_line_number = strtol(argv[2], &ptr, 10);
        printf("Focusing processing on line: %d\n", debug_line_number);
    }

    FILE * fp = openFile(filename);

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    int total = 0;
    int line_number = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        if (debug_line_number != -1 && ++line_number != debug_line_number){
            continue;
        }

        int cursor = 2;
        while (line[cursor++] != ':');
        while (0 == isdigit(line[cursor++]));
        cursor--;

        int winning[10];
        int winning_index = 0;
        int s, e;
        while (line[cursor] != '|'){
            int winner = extractNumber(line, &cursor);
            winning[winning_index++] = winner;
        }
        printf("found all winning numbers\n");
        for (int j = 0; j < 10; j++){
            printf("%d ", winning[j]);
        }
        printf("\n");

        while (0 == isdigit(line[++cursor]));

        int row_total = 0;
        while (cursor < strlen(line)){
            int possible = extractNumber(line, &cursor);
            for (int i = 0; i < 10; i++){
                if (possible == winning[i]){
                    if (row_total == 0) row_total = 1;
                    else row_total = row_total * 2;
                    break;
                }
            }
        }
        printf("Row Total: %d\n", row_total);
        total = total + row_total;
    }

    printf("Total: %d\n", total);

    closeFile(fp, line);
    return 0;
}






