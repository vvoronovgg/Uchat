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

long long mx_strget_longlongnum(char *s) {
    char *error1 = "In fuction 'mx_strget_intnum': the string doesn't exist";
    if (!s) {
        write(2, error1, mx_strlen(error1));
        exit(1);
        return 0;
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
    long long result = mx_atoi(number);
    mx_strdel(&number);
    //there is no check to be ensured that result isn't higher than long_long_MAX or lower than long_long_MIN
    return result;
}

// int main() {
//     int res = mx_strget_longlongnum("kkkk123");
//     printf("%d\n", res);
//     return 0;
// }
