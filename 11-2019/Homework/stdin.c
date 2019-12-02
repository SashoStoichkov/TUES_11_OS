#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "functions.h"

void stdin_input(){
    int file = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    int new_lines = 0;

    char buffer;
    while ((buffer = getchar()) != EOF){
        if (buffer == '\n'){
            new_lines++;
        }
        write(file, &buffer, 1);
    }

    close(file);

    if (new_lines <= 10){
        return_whole_file("temp.txt");
    } else {
        return_last_ten_lines_of_file("temp.txt");
    }

    remove("temp.txt");
}
