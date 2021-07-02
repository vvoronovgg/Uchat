#include "../inc/libmx.h"

char *mx_strcat(char *restricts1, const char *restricts2) {
    int restricts1Length = mx_strlen(restricts1);
    while (*restricts2) {
        restricts1[restricts1Length] = *restricts2;
        restricts1Length++;
        restricts2++;
    }
    restricts1[restricts1Length] = '\0';
    return restricts1;
}

// int main() {
//     char text[] = "Hello, Baby!";
//     char input[] = "bb ";
//     printf("%s", mx_strcat(input, text));
//     return 0;
// }
