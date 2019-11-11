int strlen(const char *arr){
    int result = 0;

    while (arr[result] != '\0')
        result++;

    return result;
}