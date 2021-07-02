#include "server.h"

#define E "\n\n---------error---------\n"
#define HYPHEN "\n----------------------\n\n"

void print_error(char *str) {
    if (!str)
        return;

    write(2, E, strlen(E));
    write(2, str, strlen(str));
    write(2, HYPHEN, strlen(HYPHEN));
}
