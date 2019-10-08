void *read_image(const char *filepath);

int main(int argc, const char* argv[]){
    void *img = read_image(argv[1]);

    img += 18;
    printf("BMP image width: %d\n", *(int *) img);

    img += 4;
    printf("BMP image height: %d\n", *(int *) img);

    return 0;
}