#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void inversion(char **str) {
    if (!*str)
        return;
        
    for (int i = 0; (*str)[i] != '\0'; i++) 
        (*str)[i] = ~(*str)[i];
}
