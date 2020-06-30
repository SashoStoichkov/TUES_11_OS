#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char detectType(struct stat * st);

int main(int argc, char *const argv[]) {

    for (int i = 1; i < argc; i++) {
        struct stat s;
        stat(argv[i], &s);
        if (S_ISDIR(s.st_mode)) {
            DIR *dir = opendir(argv[i]);
            struct dirent *entry;

            while (entry = readdir(dir)) {
                struct stat st;
                char name[256];
                strcpy(name, argv[i]);
                strcat(name, "/");
                strcat(name, entry->d_name);
                stat(name, &st);

                if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
                    char type = detectType(&st);
                    printf("%c %s\n", type, name);
                }
            }
        }

    }

    return 0;
}

char detectType(struct stat * st) {
    if (S_ISREG(st->st_mode)) return '-';
    else if (S_ISDIR(st->st_mode)) return 'd';
    else if (S_ISLNK(st->st_mode)) return 'l';
    else if (S_ISCHR(st->st_mode)) return 'c';
    else if (S_ISBLK(st->st_mode)) return 'b';
    else if (S_ISSOCK(st->st_mode)) return 's';
    else if (S_ISFIFO(st->st_mode)) return 'p';
}