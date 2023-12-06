#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// If I were to do this solution over, instead of looking for numbers and then finding symbols, I would look for symbols and then look for adjacent numbers.
// Doing so would be more optimal, since you could literally just look at the surrounding indices without having to scan over a bit more
// HOWEVER there is a double-counting problem the above does not address!

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
    //printf("substring ");
    char *pointer;
    int c;

    pointer = malloc(length + 2);
    if (pointer == NULL) {
        exit(EXIT_FAILURE);
    }

    for (c = 0; c < length; c++) {
        // printf("%c", *((string + position) + c));
        *(pointer + c) = *((string + position) + c);
    }

    *(pointer + c + 1) = '\0';
    // printf("\n");

    char *end = "\0";
    //printf("substring result: %ld\n", strtol(pointer, &end, 10));
    return strtol(pointer, &end, 10);
}

int lineTotal(char *prev, char *line, char *next, size_t line_length) {

    int total = 0;
    for (int i = 0; i < line_length; i++){
        if (0 == isdigit(line[i]) || line[i] == '.'){
           printf("%c", line[i]);
            continue;
        }

        int start = i;
        if (start != 0) {
            start = start - 1;
        }

        // determine length of number
        int is_partnumber = 0;

        int end = i;
        while (isdigit(line[end])) {
            if (end == line_length - 1) break;
            if (0 == isdigit(line[end])) break;

            end++;
        }
        //printf("\nend line[%d] %c\n", end, line[end]);

        // Check the prev line
        if (prev != NULL) {
            for (int p = start; p <= end; p++){
                if (prev[p] == '.' || isdigit(prev[p])){
                    continue;
                }
                is_partnumber = 1;
                break;
            }
        }

        // Check the current line start and end index
        if (0 == is_partnumber) {
            if (i != 0 && line[start] != '.'){
                is_partnumber = 1;
            }
            else  if (end != line_length - 1 && line[end] != '.'){
                is_partnumber = 1;
            }
        }

        // Check the next line
        if (0 == is_partnumber && next != NULL) {
            for (int e = start; e <= end; e++){
                if (next[e] == '.' || isdigit(next[e])){
                    continue;
                }

                is_partnumber = 1;
                break;
            }
        }

        int length = end - i;
        if (end == line_length - 1 && 1 == isdigit(line[end])) {
            length = length + 1;
        }
        int result = substring(line, i, length);
        // printf("\nDEBUG: line_length: %zu  i: %d  end: %d  result: %d  line[i]: %c  line[end]: %c\n", line_length, i, end, result, line[i], line[end]);
        if (is_partnumber){
            total += result;
            green();
            printf("%d", result);
            reset();
        }
        else {
            printf("%d", result);
        }
        if (end < line_length - 1 || 0 == isdigit(line[end])) {
            printf("%c", line[end]);
        }
        i = end;
    }

    return total;
}

void trimNewline(char * line) {
    int length = strlen(line);
    //printf("trimNewline() char at end: %c\n", line[length - 1]);
    //printf("line: %s--------------------------\n", line);
    if (line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }
    //printf("trimmed line: %s--------------------------\n", line);
}


int sumPartnumbers(int argc, char* argv[]) {
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


    //FILE * fp = openFile("./test");
    FILE * fp = openFile(filename);

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    char * prev = NULL;
    char * next = NULL;


    int total = 0;

    read = getline(&line, &len, fp);
    read = getline(&next, &len, fp);
    trimNewline(line);
    trimNewline(next);

    size_t line_length = strlen(line);
    printf("\n\n");
    // TODO: Strip off the '\n' character from every line before processing!!!
    int done = 0;
    int line_number = 1;
    int largest = 0;
    int largest_line = 0;
    while (done == 0) {

        if (debug_line_number == -1 || line_number == debug_line_number || line_number == debug_line_number - 1 || line_number == debug_line_number + 1) {
            printf("%-5d ", line_number);
            //printf("line_number %d\n", line_number);
            //printf("PREV: %s", prev);
            //if (prev == NULL) printf("\n");
            //printf("LINE: %s", line);
            //printf("NEXT: %s", next);
            //if (next == NULL) printf("\n");

            int line_total = lineTotal(prev, line, next, line_length);
            total += line_total;
            printf("   sum %5d   total %6d", line_total, total);
            //printf("LINE TOTAL %d\n", line_total);
            //printf("New Total %d\n", total);
            if (line_total > largest){
                largest = line_total;
                largest_line = line_number;
            }
            printf("\n");
        }
        prev = line;
        line = next;
        next = NULL;

        if (read == -1){
            done = 1;
        }
        read = getline(&next, &len, fp);
        trimNewline(next);

        if (0 == strcmp(next, "")){
            next = NULL;
        }
        line_number++;
    }

    printf("Largest Line: %d  %d\n", largest_line, largest);
    printf("Total: %d\n", total);

    closeFile(fp, line);
    return total;
}






