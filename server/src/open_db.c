#include "database.h"
#include "libmx.h"

/*открывает БД*/
void open_db(sqlite3 **ppdb) {
    int open_try;
    open_try = sqlite3_open("uchat.db", &(*ppdb));
}
