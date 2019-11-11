#include <stdio.h>

void swap(void *a, void *b, size_t size){
    char *i = (char *) a;
    char *k = (char *) b;

    while (size--) {
        char t = *i; 
        *i = *k; 
        *k = t;
        
        i++; k++;
    }
}