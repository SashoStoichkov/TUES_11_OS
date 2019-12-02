#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
extern int errno;

#include "functions.h"

void return_whole_file(char *filename){
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

    while ((status = read(file, &buffer, 1)) != 0){
        if (write(STDOUT_FILENO, &buffer, 1) == -1){
            char error_message[200];

            errno = 28;

            strcpy(error_message, "tail: error writing 'standard output'");

            perror(error_message);
            break;
        }
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

void return_last_ten_lines_of_file(char *filename){
    char file_arr[chars_in_file(filename)];
    write_file_in_array(filename, file_arr);

    char last_ten[last_ten_lines_char_count(file_arr, sizeof(file_arr))];
    get_last_ten_lines(file_arr, sizeof(file_arr), last_ten);

    char buffer;

    for (int i = 2; i < sizeof(last_ten)+1; i++){
        buffer = last_ten[i];
        if (i == sizeof(last_ten)){
            break;
        }
        if (write(STDOUT_FILENO, &buffer, 1) == -1){
            char error_message[200];

            errno = 28;

            strcpy(error_message, "tail: error writing 'standard output'");

            perror(error_message);
            break;
        }
    }
}