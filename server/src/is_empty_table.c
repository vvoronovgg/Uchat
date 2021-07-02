#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);

/*проверяет: пустая ли таблица*/
bool is_empty_table(char *table_name, sqlite3 **db, errors **error) {
    char sql[25];
    char *result = NULL;

    sprintf(sql, "select count(*) from %s;", table_name);
    sqlite3_better_exec(db, sql, callback, result, error, "is_empty_table");

    if (!result)
        return 0;
    else if (result && mx_strcmp("0", result) == 0) {
        mx_strdel(&result);
        return 0;
    }
    else {
        mx_strdel(&result);
        return 1;
    }
    return 0;   //чисто для компилятора: не выполняется
}

static void save_data( char *what, char **where);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(data[0], here);
    return 0;
}

static void save_data( char *what, char **where) {
    *where = mx_strdup(what);
}
