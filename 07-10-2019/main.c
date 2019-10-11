#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

void *read_image(const char *filepath);

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main(int argc, const char* argv[]){
    void *img = read_image(argv[1]);

    // img += 18;
    // printf("width = %d\n", *(int *) img);

    // img += 4;
    // printf("height = %d\n", *(int *) img);

    if (img == NULL){
        printf("Unable to open file\n");
        return 0;
    }

    if (strcmp(get_filename_ext(argv[1]), "png") != 0){
        printf("Unable to parse file\n");
        return 0;
    }

    uint32_t *width = img + 16;
    uint32_t *height = img + 20;

    printf("PNG image width: %d\n", ntohl(*width));
    printf("PNG image height: %d\n", ntohl(*height));

    FILE *fp = fopen(argv[1], "rb");
    fseek(fp, 0, SEEK_END);
    long int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);

    printf("PNG file size: %ld\n", file_size);

    return 0;
}
