#include <stdio.h>
#include <string.h>

void *read_image(const char *filepath);

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main(int argc, const char* argv[]){
    void *img = read_image(argv[1]);

    if (strcmp(get_filename_ext(argv[1]), "png") != 0){
        printf("Unable to parse file\n");
        return 0;
    }
    
    if (img == NULL){
        printf("Unable to open file\n");
        return 0;
    }

    img += 17;
    printf("PNG image width: %d\n", *(int *) img);

    img += 7;
    printf("PNG image height: %d\n", *(int *) img - 8);

    return 0;
}