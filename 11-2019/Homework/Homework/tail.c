//------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// Да се реализира стандартната UNIX команда tail.
//------------------------------------------------------------------------

#include <unistd.h>

int main(int argc, char *argv[]){

    execvp("tail", argv);
    return 0;
}