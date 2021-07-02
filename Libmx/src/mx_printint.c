#include "../inc/libmx.h"

void mx_printint(int n) {
    long buffer = n;

    if (buffer < 0) {
        mx_printchar('-');
        buffer *= -1;
    }
    if (buffer / 10 != 0) {
        mx_printint(buffer / 10);
    }
    mx_printchar(buffer % 10 + '0');
}

/* int main () {
    mx_printint(-10090961);
    return 0;
}
 */
