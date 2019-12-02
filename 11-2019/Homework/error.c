#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
extern int errno;

#include "functions.h"

void no_such_file_or_directory_error(char *filename){
    char error_message[200];

    errno = 2;

    strcpy(error_message, "tail: cannot open '");
    strcat(error_message, filename);
    strcat(error_message, "' for reading");

    perror(error_message);
    // write(STDERR_FILENO, error_message, strlen(error_message));
}

void is_a_directory_error(char *filename){
    char error_message[200];

    errno = 21;

    strcpy(error_message, "tail: error reading '");
    strcat(error_message, filename);
    strcat(error_message, "'");

    perror(error_message);
    // write(STDERR_FILENO, error_message, strlen(error_message));
}

void input_output_error(char *filename){
    char error_message[200];

    errno = 5;

    strcpy(error_message, "tail: error reading '");
    strcat(error_message, filename);
    strcat(error_message, "'");

    perror(error_message);
    // write(STDERR_FILENO, error_message, strlen(error_message));
}