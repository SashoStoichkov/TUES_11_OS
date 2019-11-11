#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    for (int i = 1; i < argc; i++){

        char file_name[100];
        strcpy(file_name, "==> ");
        strcat(strcat(file_name, argv[i]), " <==\n");

        write(STDOUT_FILENO, file_name, strlen(file_name));

        int file = open(argv[i], O_RDONLY);
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

        write(STDOUT_FILENO, "\n", 1);

        close(file);
    }

    return 0;
}