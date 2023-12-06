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

int map(int dest, int src, int len, int origin){

    if (origin < src || origin > src + len - 1){
        return -1;
    }

    return dest + (origin - src);
}

int advance(char * line, size_t len, FILE * fp, ssize_t read, int digits){
    int advanced = 0;
    while (digits == isdigit(line[0])){
        read = getline(&line, &len, fp);
        advanced++;
    }
    return advanced;
}

void parseSection(int ***maps, char * line, size_t len, FILE * fp, ssize_t read, int i1) {

    int i2 = 0;
    while (1 == isdigit(line[0])) {
        read = getline(&line, &len, fp);

        int line_len = strlen(line);
        int cursor = 0;

        maps[i1][i2][0] = extractNumber(line, &cursor);
        maps[i1][i2][1] = extractNumber(line, &cursor);
        maps[i1][i2][2] = extractNumber(line, &cursor);

        i2++;
    }
}


int run(int argc, char* argv[]) {
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

    read = getline(&line, &len, fp);
    int seed_count = 0;
    int cursor = 6;
    int first_line_length = strlen(line);
    int in_number = 0;
    while (cursor < first_line_length){

        if (in_number && 0 == isdigit(line[cursor])){
            in_number = 0;
        }
        else if (0 == in_number && isdigit(line[cursor])){
            seed_count++;
            in_number = 1;
        }
        cursor++;
    }

    int * seeds = malloc(seed_count);
    cursor = 6;
    in_number = 0;
    int s,e;
    int seed_index = 0;
    printf("Identified seeds:");
    while (cursor < first_line_length){
        int seed = extractNumber(line, &cursor);
        seeds[seed_index++] = seed;
        printf(" %d", seed);
    }
    printf("\n");

    int mappings[7];
    advance(line, len, fp, read, 0);
    int seed_to_soil_mappings = advance(line, len, fp, read, 1);
    mappings[0] = seed_to_soil_mappings;

    advance(line, len, fp, read, 0);
    int soil_to_fertilizer_mappings = advance(line, len, fp, read, 1);
    mappings[1] = soil_to_fertilizer_mappings;

    advance(line, len, fp, read, 0);
    int fertilizer_to_water_mappings = advance(line, len, fp, read, 1);
    mappings[2] = fertilizer_to_water_mappings;

    advance(line, len, fp, read, 0);
    int water_to_light_mappings = advance(line, len, fp, read, 1);
    mappings[3] = water_to_light_mappings;

    advance(line, len, fp, read, 0);
    int light_to_temperature_mappings = advance(line, len, fp, read, 1);
    mappings[4] = light_to_temperature_mappings;

    advance(line, len, fp, read, 0);
    int temperature_to_humidity_mappings = advance(line, len, fp, read, 1);
    mappings[5] = temperature_to_humidity_mappings;

    advance(line, len, fp, read, 0);
    int humidity_to_location_mappings = advance(line, len, fp, read, 1);
    mappings[6] = humidity_to_location_mappings;

    closeFile(fp, line);

    int ***maps = (int ***)malloc(7 * sizeof(int**));
    for (int i = 0; i < 7; i++){
        maps[i] = (int **)malloc(mappings[i] * sizeof(int *));
        for (int j = 0; j < mappings[i]; j++){
            maps[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }

    FILE * fp2 = openFile(filename);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 0);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 1);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 2);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 3);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 4);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 5);

    advance(line, len, fp2, read, 0);
    parseSection(maps, line, len, fp2, read, 6);

    closeFile(fp2, line);

    int lowest = -1;
    for (int s = 0; s < seed_count; s++){
        int transfer = seeds[s];

        for (int i = 0; i < 7; i++){
            int type = 0;
            while (maps[i][type] != NULL){

                int result = map(maps[i][type][0], maps[i][type][1], maps[i][type][2], transfer);
                if (result != -1){
                   transfer = result;
                   break;
                }
                type++;
            }
        }
       if (lowest == -1){
           lowest = transfer;
       }

       if (transfer < lowest){
            lowest = transfer;
       }
    }

    printf("Lowest: %d\n", lowest);

    return 0;
}






