#include "../inc/libmx.h"

static void StrNumber(char *str, char **number, int sign) {
    int Numlen = 0;

    if (sign == 1) {
        Numlen++;
    }   
    for (int i = sign; mx_is_digit(str[i]); i++, Numlen++) {
    }
    *number = mx_strnew(Numlen);
    for (int i = 0; i < Numlen; i++) {
        (*number)[i] = str[i];
    }
}

char *mx_strget_numberstr(char *s) {
    char *error1 = "In fuction 'mx_strget_numberstr': the string doesn't exist";
    if (!s) {
        write(2, error1, mx_strlen(error1));
        exit(1);
        return NULL;
    }
    int Strlen = mx_strlen(s);
    char *Follower = NULL;
    char *number;
    bool stop = false;

    for (int i = 0; i < Strlen && !stop; i++) {
        if (s[i] == '-' && i + 1 < Strlen && mx_is_digit(s[i + 1])) {
            Follower = &s[i];
            StrNumber(Follower, &number, 1);
            stop = true;
        }
        if (mx_is_digit(s[i])) {
            Follower = &s[i];
            StrNumber(Follower, &number, 0);
            stop = true;
        }
    }
    return number;
}

// int main() {
//     int res = mx_strget_longlongnum("kkkk123");
//     printf("%d\n", res);
//     return 0;
// }
