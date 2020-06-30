//------------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: LS
// FILE NAME: main.c
// FILE PURPOSE:
// Да се реализира ls
//------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct flags_t {
    int l;
    int a;
    int r;
} flags_t;

//------------------------------------------------------------------------------
// FUNCTION: print_file_permissions()
// извежда правата на даден файл за всяка от групите
// PARAMETERS:
// -> mode_t mode -> мод на даден файл
//------------------------------------------------------------------------------
void print_file_permissions(mode_t mode) {
// =============================================================================
    putchar((mode & S_IRUSR) ? 'r' : '-'); //
    putchar((mode & S_IWUSR) ? 'w' : '-'); // ----> user
    putchar((mode & S_IXUSR) ? 'x' : '-'); //
// =============================================================================
    putchar((mode & S_IRGRP) ? 'r' : '-'); //
    putchar((mode & S_IWGRP) ? 'w' : '-'); // ----> group
    putchar((mode & S_IXGRP) ? 'x' : '-'); //
// =============================================================================
    putchar((mode & S_IROTH) ? 'r' : '-'); //
    putchar((mode & S_IWOTH) ? 'w' : '-'); // ----> others
    putchar((mode & S_IXOTH) ? 'x' : '-'); //
// =============================================================================
}

//------------------------------------------------------------------------------
// FUNCTION: print_file_type()
// извежда типа на даден файл
// PARAMETERS:
// -> mode_t mode -> мод на даден файл
//------------------------------------------------------------------------------
void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) putchar('-'); // -----------> обикновен файл
    else if (S_ISDIR(mode)) putchar('d'); // ------> директория
    else if (S_ISBLK(mode)) putchar('b'); // ------> блоково устройство
    else if (S_ISCHR(mode)) putchar('c'); // ------> символно устройство
    else if (S_ISFIFO(mode)) putchar('p'); // -----> програмен поток
    else if (S_ISLNK(mode)) putchar('l'); // ------> символна връзка
    else if (S_ISSOCK(mode)) putchar('s'); // -----> сокет
}

//------------------------------------------------------------------------------
// FUNCTION: get_long_file_info()
// извежда детайлна информация за даден файл при наличие на -l флаг
// и връща броя блокове на този файл
// PARAMETERS:
// -> struct stat st -> структура с пълната информация за даден файл
//------------------------------------------------------------------------------
long get_long_file_info(struct stat st) {
    print_file_type(st.st_mode);
    print_file_permissions(st.st_mode);

    printf(" %ld", st.st_nlink);

    struct passwd *pwd_user;
    pwd_user = getpwuid(st.st_uid);
    printf(" %s", pwd_user->pw_name);

    struct passwd *pwd_group;
    pwd_group = getpwuid(st.st_gid);
    printf(" %s", pwd_group->pw_name);

    printf(" %ld", st.st_size);

    time_t now;
    time(&now);

    double seconds_difference = difftime(now, mktime(localtime(&(st.st_mtime))));
    char date[20];

    // Формулата може да бъде намерена тук: https://www.checkyourmath.com/convert/time/seconds_months.php
    if (seconds_difference / 2628002.88 > 6) {
        strftime(date, 20, "%b %e %Y", localtime(&(st.st_mtime)));
    } else {
        strftime(date, 20, "%b %e %H:%M", localtime(&(st.st_mtime)));
    }
    printf(" %s", date);

    return st.st_blocks;
}

//------------------------------------------------------------------------------
// FUNCTION: get_info()
// проверява подадените флагове за даден файл
// и връща броя блокове на този файл
// PARAMETERS:
// -> char *path -------> абсолютен път до файл
// -> char *filename ---> име на файл
// -> flags_t flags ----> подадени флагове
//------------------------------------------------------------------------------
long get_info(char *path, char *filename, flags_t flags) {
    long blocks = 0;
    struct stat st;

    if (stat(path, &st) == 0) {
        if (flags.l == 1) {
            if (flags.a == 1) {
                if ((strcmp(filename, ".") != 0) && (strcmp(filename, "..") != 0)) {
                    blocks = get_long_file_info(st);
                    printf(" %s\n", filename);
                }
            } else {
                if (filename[0] != '.') {
                    blocks = get_long_file_info(st);
                    printf(" %s\n", filename);
                }
            }
        } else {
            if (flags.a == 1) {
                if ((strcmp(filename, ".") != 0) && (strcmp(filename, "..") != 0)) {
                    print_file_type(st.st_mode);
                    printf(" %s\n", filename);
                }
            } else {
                if (filename[0] != '.') {
                    print_file_type(st.st_mode);
                    printf(" %s\n", filename);
                }
            }
        }
    } else {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    return blocks;
}

//------------------------------------------------------------------------------
// FUNCTION: ls()
// The "ls" function of the "ls"
// PARAMETERS:
// -> char *path -------> абсолютен път до файл
// -> char *filename ---> име на файл
// -> flags_t flags ----> подадени флагове
//------------------------------------------------------------------------------
void ls(char *path, char *filename, flags_t flags) {
    struct stat s;
    if (stat(path, &s) == 0) {
        if (flags.r == 1) {
            printf("%s:\n", path);
        }

        int dirs = 0;
        char ** directories = (char **) malloc(dirs * sizeof(char *));

        if (S_ISDIR(s.st_mode)) {
            DIR *dir = opendir(path);
            struct dirent *entry;

            long total = 0;

            while ((entry = readdir(dir))) {
                char full_path[FILENAME_MAX];
                strcpy(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, entry->d_name);

                struct stat st;
                stat(full_path, &st);

                if (S_ISDIR(st.st_mode) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {
                    if (flags.a == 1 || entry->d_name[0] != '.') {
                        directories = realloc(directories, ++dirs * sizeof(char *));
                        directories[dirs - 1] = (char *) malloc((strlen(full_path) + 1) * sizeof(char));
                        strcpy(directories[dirs - 1], full_path);
                    }
                }

                total += get_info(full_path, entry->d_name, flags);
            }

            if (flags.l == 1) {
                printf("total %ld\n", total / 2);
            }

            closedir(dir);
        } else {
            get_info(path, filename, flags);
        }

        if (flags.r == 1) {
            for (int i = 0; i < dirs; i++) {
                printf("\n");
                ls(directories[i], "", flags);
                free(directories[i]);
            }
        }

        free(directories);
    } else {
        perror("stat");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *const argv[]) {
    flags_t flags;
    flags.l = 0;
    flags.a = 0;
    flags.r = 0;

    int opt;
    while ((opt = getopt(argc, argv, "lAR")) != -1) {
        switch (opt) {
            case 'l': flags.l = 1; break;
            case 'A': flags.a = 1; break;
            case 'R': flags.r = 1; break;
            default: return -1;
        }
    }

    if (argc == optind) {
        ls(".", "", flags);
    } else {
        for (int i = optind; i < argc; i++) {
            struct stat s;
            if (stat(argv[i], &s) == 0) {
                if ((access(argv[i], X_OK) == 0)) {
                    if (i != optind) {
                        printf("\n");
                    }

                    if (i >= optind && S_ISDIR(s.st_mode) && argc != optind+1) {
                        printf("%s:\n", argv[i]);
                    }
                    ls(argv[i], argv[i], flags);

                    if (stat(argv[i+1], &s) == 0) {
                        if (!S_ISDIR(s.st_mode)) printf("\n");
                    }
                } else {
                    if (S_ISDIR(s.st_mode)) {
                        char *error_str = (char *) malloc((30 + strlen(argv[i])) * sizeof(char));
                        strcpy(error_str, "ls: cannot open directory '");
                        strcat(error_str, argv[i]);
                        strcat(error_str, "'");
                        perror(error_str);
                        free(error_str);
                    } else {
                        ls(argv[i], argv[i], flags);
                    }
                }
            } else {
                char *error_str = (char *) malloc((21 + strlen(argv[i])) * sizeof(char));
                strcpy(error_str, "ls: cannot access '");
                strcat(error_str, argv[i]);
                strcat(error_str, "'");
                perror(error_str);
                free(error_str);
            }
        }
    }

    return 0;
}