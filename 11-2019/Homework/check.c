#include <string.h>

#include "functions.h"

int all_arguments_are_dashes(int argc, char *argv[]){
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-") != 0){
            return 0;
        }
    }

    return 1;
}