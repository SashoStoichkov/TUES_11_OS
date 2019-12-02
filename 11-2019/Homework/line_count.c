#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
extern int errno;

#include "functions.h"

int lines_in_file(char *filename){
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

    int number_of_lines = 0;

    while ((status = read(file, &buffer, 1)) != 0){
        if (buffer == '\n'){
            number_of_lines++;
        };
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

    return number_of_lines + 1;
}