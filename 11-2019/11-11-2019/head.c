#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int file = open("a.txt", O_RDONLY);
    char buff;
    int status;

    int number_of_new_lines = 0;

    while ((status = read(file, &buff, 1)) != 0){
        if (buff == '\n'){
            number_of_new_lines++;
        }

        write(STDOUT_FILENO, &buff, 1);

        if (number_of_new_lines == 10){
            break;
        }
    }

    close(file);

    return 0;
}