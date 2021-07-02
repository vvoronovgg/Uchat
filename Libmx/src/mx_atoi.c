#include "../inc/libmx.h"

long long mx_atoi(char *str) {
    int start = 0;
    long long IntLen = mx_strlen(str);
    long long Nten;
    long long Int = 0;
    long long digit;

    if (str[0] == '-')
        start = 1;
    if (start)
        IntLen--;
    for (int i = start; str[i] != '\0'; i++) {
        Nten = mx_pow(10, IntLen - 1);
        digit = str[i] - '0';
        Int = Int + digit * Nten;
        IntLen--;
    }
    if (start)
        Int *= -1;
    return Int;
}

// int main () {
//     printf("%lld", mx_atoi("2147483648"));
//     return 0;
// }
