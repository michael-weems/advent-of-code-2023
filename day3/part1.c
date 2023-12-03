#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// If I were to do this solution over, instead of looking for numbers and then finding symbols, I would look for symbols and then look for adjacent numbers.
// Doing so would be more optimal, since you could literally just look at the surrounding indices without having to scan over a bit more
// HOWEVER there is a double-counting problem the above does not address!


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
    printf("substring ");
    char *pointer;
    int c;

    pointer = malloc(length + 2);
    if (pointer == NULL) {
        exit(EXIT_FAILURE);
    }

    for (c = 0; c < length; c++) {
        printf("%c", *((string + position) + c));
        *(pointer + c) = *((string + position) + c);
    }

    *(pointer + c + 1) = '\0';
    printf("\n");

    char *end = "\0";
    printf("substring result: %ld\n", strtol(pointer, &end, 10));
    return strtol(pointer, &end, 10);
}

int lineTotal(char *prev, char *line, char *next, size_t line_length) {
    printf("lineTotal()\n");

    int total = 0;
    for (int i = 0; i < line_length; i++){
        printf("i = %d, c = %c\n", i, line[i]);
        if (0 == isdigit(line[i]) || line[i] == '.'){
            printf("Skipping index %d - %c\n", i, line[i]);
            continue;
        }

        int start = i;
        if (start != 0) {
            start = start - 1;
        }

        // determine length of number
        int is_partnumber = 0;

        int end = i;
        while (end < line_length && isdigit(line[end++]));
        end--;

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
            if (i != 0){
                if (line[start] != '.' && 1 == isdigit(line[start])){
                    is_partnumber = 1;
                }
            }
            else {
                printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
                printf("line[end] %c\n", line[end]);
                if (line[end] != '.' && 0 == isdigit(line[end])){
                    is_partnumber = 1;
                }
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

        if (is_partnumber){
            int length = end - i;
            //if (0 == isdigit(line[end])) {
            //    length = end - 1 - i;
           // }
            int result = substring(line, i, length);
            total += result;
            printf("DEBUG: i: %d  -  start: %d  - end: %d  - length: %d\n", i, start, end, length);
            printf("partnumber: %d  - current line_total: %d\n", result, total);
            //total += atoi(substring(line, i, length));
        }

        i = end;
        printf("DEBUG: i = end: i: %d  end: %d\n", i, end);
    }

    return total;
}

char *readline(ssize_t read, size_t len, FILE * fp, size_t line_length) {
  char *line;

   line = malloc(line_length + 1);

    read = getline(&line, &len, fp);

   *(line + line_length + 1) = '\0';
   return line;
}

int main(void){

    //FILE * fp = openFile("./test");
    FILE * fp = openFile("./input");

    char * line = NULL;
    ssize_t read;
    size_t len = 0;

    char * prev = NULL;
    char * next = NULL;


    int total = 0;

    read = getline(&line, &len, fp);
    read = getline(&next, &len, fp);

    size_t line_length = strlen(line);
    printf("---------------------------------------------------------\n\n");
    printf("line_length %zu\n", line_length);

    int done = 0;

    while (done == 0) {
        printf("PREV: %s", prev);
        printf("LINE: %s", line);
        printf("NEXT: %s", next);

        int line_total = lineTotal(prev, line, next, line_length);
        total += line_total;

        printf("LINE TOTAL %d\n", line_total);

        prev = line;
        line = next;
        next = NULL;

        if (read == -1){
            done = 1;
        }
        read = getline(&next, &len, fp);
        printf("\n");
    }

    printf("Total: %d\n", total);

    closeFile(fp, line);
    exit(EXIT_SUCCESS);
}
