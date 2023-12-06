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

int cardDupes(int argc, char* argv[]) {
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

    FILE * fp = openFile(filename);

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    int total = 0;
    int cards[219];
    for (int i = 0; i < 219; i++){
        cards[i] = 1;
    }

    int line_number = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);

        ++line_number;

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
        printf("\n");

        while (0 == isdigit(line[++cursor]));

        int winner_count = 0;
        while (cursor < strlen(line)){
            int possible = extractNumber(line, &cursor);
            for (int i = 0; i < 10; i++){
                if (possible == winning[i]){
                    printf("found winner: %d\n", possible);
                    winner_count = winner_count + 1;
                    break;
                }
            }
        }

        int copy_amount = cards[line_number - 1];
        printf("cards[%d]  %d\n", line_number - 1, cards[line_number - 1]);
        for (int i = line_number; i < line_number + winner_count; i++){
            if (i > 219 - 1) break;

            int before = cards[i];
            cards[i] = cards[i] + copy_amount;
            int diff = cards[i] - before;
            printf("Adding %d copies to Card %d (previously had %d)\n", diff, i + 1, before);
        }

        total += cards[line_number - 1];
    }

    for (int i = 0; i < 6; i++){
        printf("%d ", cards[i]);
    }
    printf("\n");

    printf("Total: %d\n", total);

    closeFile(fp, line);
    return 0;
}






