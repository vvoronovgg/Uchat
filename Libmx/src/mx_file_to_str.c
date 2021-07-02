#include "../inc/libmx.h"

static char *EmptyFileStr(int fd, int *Strlen) {
    char buf;
    char *Str = NULL;
    while (read(fd, &buf, 1))
        (*Strlen)++;
    close(fd);
    Str = mx_strnew(*Strlen);
    if (!Str)
        return NULL;
    return Str;
}

char *mx_file_to_str(const char *file) {
    if (!file)
        return NULL;
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return NULL;
    char *Str = NULL;
    int StrLen = 0;
    Str = EmptyFileStr(fd, &StrLen);
    fd = open(file, O_RDONLY);

    if (fd == -1)
        return NULL;
    for (int i = 0; i < StrLen; i++) {
        read(fd, &Str[i], 1);
    }
    close(fd);
    return Str;
}

// int main () {
//     printf("%s\n", mx_file_to_str("file.txt"));
//     return 0;
// }
