#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sum-partnumbers.c"

void success(){
    green();
    printf("SUCCESS: ");
    reset();
}

void failure() {
    red();
    printf("FAILURE: ");
    reset();
}


void it_handles_start_of_line_partnumber(){
    char *argv[] = {"./tests", "./test-data/start-of-line-partnumber"};
    int sum = sumPartnumbers(2, argv);
    if (sum == 5){
        success();
        printf("it_handles_start_of_line_partnumber\n");
    }
    else {
        failure();
        printf("it_handles_start_of_line_partnumber\n");
    }
}

void it_handles_start_of_line_number() {
    char *argv[] = {"./tests", "./test-data/start-of-line-number"};
    int sum = sumPartnumbers(2, argv);
    if (sum == 4){
        success();
        printf("it_handles_start_of_line_number\n");
    }
    else {
        failure();
        printf("it_handles_start_of_line_number\n");
    }
}

void it_handles_end_of_line_partnumber(){
    char *argv[] = {"./tests", "./test-data/end-of-line-partnumber"};
    int sum = sumPartnumbers(2, argv);
    if (sum == 5){
        success();
        printf("it_handles_end_of_line_partnumber\n");
    }
    else {
        failure();
        printf("it_handles_end_of_line_partnumber\n");
    }
}

void it_handles_end_of_line_number() {
    char *argv[] = {"./tests", "./test-data/end-of-line-number"};
    int sum = sumPartnumbers(2, argv);
    if (sum == 1){
        success();
        printf("it_handles_end_of_line_number\n");
    }
    else {
        failure();
        printf("it_handles_end_of_line_number\n");
    }
}



int main(int argc, char* argv[]){
    it_handles_start_of_line_partnumber();
    it_handles_start_of_line_number();

    it_handles_end_of_line_partnumber();
    it_handles_end_of_line_number();


}
