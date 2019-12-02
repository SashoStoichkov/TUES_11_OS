#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
extern int errno;

#include "functions.h"

int chars_in_file(char *filename){
    int file = open(filename, O_RDONLY);

    if (file == -1){
        char error_message[200];

        errno = 2;

        strcpy(error_message, "tail: cannot open '");
        strcat(error_message, filename);
        strcat(error_message, "' for reading");

        perror(error_message);
        // write(STDERR_FILENO, error_message, strlen(error_message));
    }

    char buffer;
    int status;

    int char_count = 0;

    while ((status = read(file, &buffer, 1)) != 0){
        char_count++;
    }

    if (close(file) == -1){
        char error_message[200];

        errno = 5;

        strcpy(error_message, "tail: error reading '");
        strcat(error_message, filename);
        strcat(error_message, "'");

        perror(error_message);
        // write(STDERR_FILENO, error_message, strlen(error_message));
    }

    return char_count;
}

int last_ten_lines_char_count(char *file_arr, int sizeof_file_arr){
    int char_count = 0;
    int count_of_new_lines = 0;

    for (int i = sizeof_file_arr; count_of_new_lines <= 10; i--){
        if (file_arr[i] == '\n'){
            count_of_new_lines++;
        }
        char_count++;
    }

    return char_count;
}