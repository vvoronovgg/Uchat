#include "../inc/libmx.h"

static int LengthOfNumber(long number, int counter) {
    if (number < 0) {
        counter++;
        number *= -1;
    }
    if (number / 10 != 0) {
        counter++;
        return LengthOfNumber(number / 10, counter);
    }
    return counter;
}

static char *DownTo(int Left, char *arr, int size) {
    char buffer;
    int Right = size + Left;

    for (int i = Left; i <= Right; i++) {
        buffer = arr[i];
        arr[i] = arr[Right];
        arr[Right] = buffer;
        Right--;
    }
    return arr;
}

char *mx_itoa(int number) {
    if (number == -2147483648)
        return "-2147483648";
    int index = 0;
    int CopyIndex;

    if (number < 0)
        index = 1;
    CopyIndex = index;
    int LengthOfInt = LengthOfNumber(number, 1) ;
    
    char *OutputStr = NULL;
    OutputStr = mx_strnew(LengthOfInt);
    if (index == 1) {
        OutputStr[0] = '-';
        number *= - 1;
        LengthOfInt --;
    }
    while (number / 10 != 0) {
        OutputStr[index] = (number % 10) + '0';
        number /= 10;
        index++;
    }
    OutputStr[index] = (number % 10 ) + '0';
    OutputStr = DownTo(CopyIndex, OutputStr, LengthOfInt - 1);
    return OutputStr;
}

// int main() {
//     char *s = NULL;
//     s = mx_itoa(-2147483647);
//     printf("%s\n", s);
//     free(s);
//     return 0;
// }
