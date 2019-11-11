#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int my_strlen(const char *arr){
//     int result = 0;

//     while (arr[result] != '\0')
//         result++;

//     return result;
// }

// char* strcat(char *destination, const char *source){
//     strcpy(destination + strlen(destination), source);
//     return destination;
// }

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

// typedef struct {
//     size_t size;
//     size_t capacity;
//     int *elements;
// } stack;

// void stack_init(stack *s, int cap){
//     s->size = 0;
//     s->capacity = cap;
//     s->elements = NULL;
// }

// void stack_destroy(stack *s){
//     free(s->elements);
//     s->size = 0;
// }

// int stack_empty(stack *s){
//     if (s->size <= 0) return 1;
//     return 0;
// }

// void stack_push(stack *s, int num){
//     s->elements = (int *) realloc (s->elements, (sizeof(int) * (++s->size)));
//     s->elements[s->size-1] = num;
// }

// int stack_top(stack *s){
//     return s->elements[s->size-1];
// }

// void stack_pop(stack *s){
//     s->elements = (int *) realloc (s->elements, sizeof(int) * (--s->size));
// }

int main(){

    // char name[100] = "Pesho";
    // char l_name[100] = " Goshev";

    // printf("%d\n", my_strlen(name));

    // printf("%s\n", strcat(name, l_name));

    // int a = 5;
    // int b = 6;

    // swap(&a, &b);

    // printf("%d %d\n", a, b);

    // printf("%p\n", my_strdup(name));

    // stack s;
    // stack_init(&s, 25);

    // for (int i = 0; i <= s.capacity; i++){
    //     stack_push(&s, i);
    //     printf("Top: %d\n", stack_top(&s));
    // }

    // printf("Pop:\n");

    // for (int i = 0; i <= s.capacity; i++){
    //     printf("Top: %d\n", stack_top(&s));
    //     stack_pop(&s);
    // }

    // stack_destroy(&s);

    return 0;
}