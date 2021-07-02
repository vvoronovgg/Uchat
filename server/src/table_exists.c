#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void make_sql_table_exists(char sql[N], char *table_name);

static int callback(void *here, int count, char **data, char **columns);

/*возвращает: 
    NULL - не существует таблица table_name
    table_name (динамическая память) - если существует
*/
char *table_exists(char *table_name, sqlite3 **db, errors **error) {
    if (!table_name || !db || !*db || (*error)->error_message)
        return NULL;
    
    char sql[N];
    char *exists = NULL;
    make_sql_table_exists(sql, table_name);
    mx_printstr(sql);
    sqlite3_better_exec(db, sql, callback, exists, error, "table_exists");
    return exists;
}

void make_sql_table_exists(char sql[N], char *table_name) {
    if (!sql || !table_name)
        return;
    
    sprintf(sql, "SELECT name FROM sqlite_master WHERE type='table' AND name='%s';", table_name);
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
