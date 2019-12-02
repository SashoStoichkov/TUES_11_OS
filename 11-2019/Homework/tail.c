//------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// Да се реализира стандартната UNIX команда tail.
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include <errno.h>
extern int errno;

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "functions.h"

int main(int argc, char *argv[]){
    if (argc == 1 || all_arguments_are_dashes(argc, argv)){
        stdin_input();
        return 0;
    }

    for (int i = 1; i < argc; i++){
        char *filename = argv[i];

        struct stat buffer;
        stat(filename, &buffer);

        if (S_ISDIR(buffer.st_mode)){
            if (argc > 2){
                add_file_header(filename, i);
            }
            is_a_directory_error(filename);
            continue;
        }

        if (strcmp(filename, "-") == 0){
            add_stdin_header(i);
            stdin_input();
        } else {
            if (open(filename, O_RDONLY) == -1){
                no_such_file_or_directory_error(filename);
                continue;
            }

            if (argc > 2){
                add_file_header(filename, i);

                if (S_ISDIR(buffer.st_mode)){
                    is_a_directory_error(filename);
                    continue;
                }
            }

            if (lines_in_file(filename) <= 10){
                return_whole_file(filename);
            } else {
                return_last_ten_lines_of_file(filename);
            }
        }

        if (close(open(filename, O_RDONLY)) == -1 && strcmp(filename, "-") != 0){
            input_output_error(filename);
        }
    }

    return 0;
}
