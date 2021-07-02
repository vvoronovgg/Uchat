#include "../inc/libmx.h"

static unsigned int LengthOfNumber(unsigned long number, int counter) {
    if (number / 10 != 0) {
        counter++;
        return LengthOfNumber(number / 10, counter);
    }
    return counter;
}

static char *Divide16FillArr(unsigned long number, char *MaxStr, int index) {
    if (number < 16) {
        if (number < 10)
            MaxStr[index] = number + '0';
        else
            MaxStr[index] = number + 'W';
        return MaxStr;
    }
    else {
        int Hex = number % 16;
        if (Hex < 10)
            MaxStr[index] = Hex + '0';
        else
            MaxStr[index] = Hex + 'W';
        index++;
        return Divide16FillArr(number / 16, MaxStr, index);
    }
}

static char *ArrDownTo(char *arr, int size) {
    char buffer;
    int Left = 0;
    int Right = size - 1;

    while (Left <= Right) {
            buffer = arr[Left];
            arr[Left] = arr[Right];
            arr[Right] = buffer;
            Right--;
            Left++;
    }
    return arr;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    int LengthN = LengthOfNumber(nbr, 1);
    char *OutputStr = NULL;
    OutputStr = mx_strnew(LengthN);
    OutputStr = Divide16FillArr(nbr, OutputStr, 0);
    LengthN = mx_strlen(OutputStr);
    OutputStr = ArrDownTo(OutputStr, LengthN);
    return OutputStr;
}

// int main() {
//     char *s = NULL; 
//     s = mx_nbr_to_hex(4294967295);
//     printf("%s", s);
//     free(s);
// }
