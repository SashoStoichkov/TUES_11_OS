#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int type_file(mode_t mode) {
    if (S_ISREG(mode)) return 1;
    else if (S_ISDIR(mode)) return -1;
    else return 0;
}

int is_big(struct stat st, long min_size) {
    if (st.st_size > min_size) return 1;
    else return 0;
}

void find_big(const char* path, long min_size) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat s;

    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            if (stat(entry->d_name, &s) != -1) {
                if (type_file(s.st_mode) == -1) { // directory
                    // recursive
                    char rec_path[FILENAME_MAX];
                    strcpy(rec_path, path);
                    strcat(rec_path, "/");
                    strcat(rec_path, entry->d_name);

                    find_big(rec_path, min_size);
                } else {
                    if (is_big(s, min_size) == 1) { // file
                        char path_to_display[FILENAME_MAX];
                        strcpy(path_to_display, path);
                        strcat(path_to_display, "/");
                        strcat(path_to_display, entry->d_name);

                        printf("%ld %s\n", s.st_size, path_to_display);
                    }
                }
            } else {
                perror("stat");
                return;
            }
        }
    }

    closedir(dir);
}

int main(int argc, char const *argv[]) {

    if (argc < 2) {
        printf("2 arguments are required!\n");
        return 2;
    } else {
        long min_size = atol(argv[1]);

        if (argc == 2) {
            find_big(".", min_size);
        } else {
            for (int i = 2; i < argc; i++) {
                struct stat st;

                if (stat(argv[i], &st) != -1) {
                    if (type_file(st.st_mode) == -1) {
                        find_big(argv[i], min_size);
                    } else {
                        printf("findbig: Not a directory\n");
                    }
                } else {
                    perror("stat");
                }
            }
        }
    }

    return 0;
}
