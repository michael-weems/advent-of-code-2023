#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generate-project.h"

int main(int argc, char* argv[]){
    int result = generateProject(argc, argv);
    exit(EXIT_SUCCESS);
}
