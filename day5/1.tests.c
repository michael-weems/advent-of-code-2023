#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "1.run.c"

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


void it_maps_correctly(){
    //char *argv[] = {"./tests", "./test-data/start-of-line-partnumber"};
    int one = map(50, 98, 2, 99);
    if (one == 51){
        success();
        printf("99 --> 51\n");
    }
    else {
        failure();
        printf("99 --> %d\n", one);
    }
}

int main(int argc, char* argv[]){
    printf("-----------------------------\n");
    printf("Mapping numbers correctly\n\n");
    it_maps_correctly();
}
