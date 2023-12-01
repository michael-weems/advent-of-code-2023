#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int containsWord(int index, char line[], char word[]){
    if (strlen(line) - index < strlen(word)){
        return 0;
    }

    for (int j = 0; j < strlen(word); j++){

        if (word[j] != line[index + j]){
            return 0;
        }
    }
    return 1;
}

/* o, t, f, s, e, n, z */
char isDigitWord(int index, char line[]){
    char c = line[index];
    if (c != 'o' && c != 't' && c != 'f' && c != 's' && c != 'e' && c != 'n' && c != 'z'){
        return 'x';
    }

    if (containsWord(index, line, "zero")){
        return '0';
    }
    if (containsWord(index, line, "one")){
        return '1';
    }

    if (containsWord(index, line, "two")){
        return '2';
    }

    if (containsWord(index, line, "three")){
        return '3';
    }
    if (containsWord(index, line, "four")){
        return '4';
    }
    if (containsWord(index, line, "five")){
        return '5';
    }
    if (containsWord(index, line, "six")){
        return '6';
    }
    if (containsWord(index, line, "seven")){
        return '7';
    }
    if (containsWord(index, line, "eight")){
        return '8';
    }
    if (containsWord(index, line, "nine")){
        return '9';
    }

    return 'x';
}

int main(void){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("./input", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int total = 0;

    while ((read = getline(&line, &len, fp)) != -1) {

        char digits[] = "xx";


        int lineLength = strlen(line);
        for (int i = 0; i < lineLength; i++) {
            char c = line[i];
            if (0 == isdigit(c)){
                c = isDigitWord(i, line);
            }

            if (c == 'x'){
                continue;
            }

            if (digits[0] == 'x'){
                digits[0] = c;
            }
            else {
                digits[1] = c;
            }
        }

        if (digits[0] == 'x'){
            total += 0;
            continue;
        }

        if (digits[1] == 'x'){
            digits[1] = digits[0];
        }

        total = total + atoi(digits);
    }

    printf("Total Calibration Number: %d\n", total);

    fclose(fp);
    if (line) {
        free(line);
    }
    exit(EXIT_SUCCESS);
}
