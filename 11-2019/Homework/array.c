#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
extern int errno;

#include "functions.h"

void write_file_in_array(char *filename, char *file_arr){
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

    int i = 0;

    while ((status = read(file, &buffer, 1)) != 0){
        file_arr[i++] = buffer;
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
}

void get_last_ten_lines(char *file_arr, int sizeof_file_arr, char *last_ten){
    char last_ten_reversed[last_ten_lines_char_count(file_arr, sizeof_file_arr)];
    int index = sizeof_file_arr;

    int last_ten_count = last_ten_lines_char_count(file_arr, sizeof_file_arr);

    for (int i = 0; i < last_ten_count; i++){
        last_ten_reversed[i] = file_arr[index--];
    }

    index = last_ten_count;

    for (int i = 0; i < last_ten_count && index >= 1; i++){
        last_ten[i] = last_ten_reversed[index--];
    }
}
