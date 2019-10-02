char* strcat(char *destination, const char *source){
    char *p[strlen(destination) + strlen(source) + 1];
    int ptr = 0;
    int temp = 0;

    while (destination[temp] != '\0'){
        p[ptr++] = destination[temp++];
    }

    temp = 0;

    while (source[temp] != '\0'){
        p[ptr++] = source[temp++];
    }

    destination = &p;

    return destination;
}