// Alexander Stoichkov

// #include <stdio.h>
// #include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct {
    char data;
    unsigned char nextElementAdress;
} block;

int main(int argc, char *argv[]){
    int file = open(argv[1], O_RDONLY);
    block bl;
    int status;

    while ((status = read(file, &bl, 2)) != 0){
        if (bl.nextElementAdress == 0){
            break;
        }
        write(STDOUT_FILENO, &bl.data, 1);
        lseek(file, bl.nextElementAdress, SEEK_SET);
    }

    write(STDOUT_FILENO, "\n", 1);

    close(file);

    return 0;
}