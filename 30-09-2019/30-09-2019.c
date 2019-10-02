#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int my_strlen(const char *arr){
//     int result = 0;

//     while (arr[result] != '\0')
//         result++;

//     return result;
// }

char* my_strcat(char *destination, const char *source){
    char p[strlen(destination) + strlen(source) + 1];
    int ptr = 0;
    int temp = 0;

    while (destination[temp] != '\0'){
        p[ptr++] = destination[temp++];
    }

    temp = 0;

    while (source[temp] != '\0'){
        p[ptr++] = source[temp++];
    }

    destination = p;
    

    return destination;
}

// void swap(int *a, int *b){
//     int temp;

//     temp = *a;
//     *a = *b;
//     *b = temp;
// }

// char *my_strdup(const char *src) {
//     char *str;
//     char *p;
//     int len = 0;

//     while (src[len]){
//         len++;
//     }

//     str = malloc(len + 1);
//     p = str;

//     while (*src){
//         *p++ = *src++;
//     }

//     *p = '\0';
//     return str;
// }

int main(){

    char *name = "Pesho";
    char *l_name = " Goshev";

    // printf("%d\n", my_strlen(name));

    printf("%s\n", my_strcat(name, l_name));

    // int a = 5;
    // int b = 6;

    // swap(&a, &b);

    // printf("%d %d\n", a, b);

    // printf("%p\n", my_strdup(name));

    return 0;
}