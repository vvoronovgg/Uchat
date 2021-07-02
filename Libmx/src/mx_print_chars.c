#include "../inc/libmx.h"

void mx_print_chars(char character, int amount) {
    for (int i = 0; i < amount; i++) {
        mx_printchar(character);
    }
}
