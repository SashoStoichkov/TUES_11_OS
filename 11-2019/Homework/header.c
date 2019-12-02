#include <string.h>
#include <unistd.h>

#include "functions.h"

void add_file_header(char *filename, int argc_index){
    char file_name[100];

    if (argc_index == 1){
        strcpy(file_name, "==> ");
    } else {
        strcpy(file_name, "\n==> ");
    }
    strcat(strcat(file_name, filename), " <==\n");

    write(STDOUT_FILENO, file_name, strlen(file_name));
}

void add_stdin_header(int argc_index){
    char header[100];

    if (argc_index == 1){
        strcpy(header, "==> standard input <==\n");
    } else {
        strcpy(header, "\n==> standard input <==\n");
    }

    write(STDOUT_FILENO, header, strlen(header));
}