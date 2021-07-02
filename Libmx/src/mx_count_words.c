#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    if (!str)
        return -1;
    bool Found_AWord = true;
    int counter = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (Found_AWord && str[i] != c) {
            counter++;
            Found_AWord = false;
        }
        else if (!Found_AWord && str[i] == c)
            Found_AWord = true;
    }
    return counter;
}

// int main () {
//     printf("%d", mx_count_words(" vbg yuu uiiu ", 'y'));
//     return 0;
// }
