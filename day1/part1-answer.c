#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
