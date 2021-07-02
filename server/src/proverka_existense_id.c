#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);
/*проверяет на существование "друга" в таблице friends_[user_id]: в случае уже существования такого "друга" в таблице возвращает true в ином false*/
bool proverka_existence_id(char *id_for_tablename, char *id_for_check_value, sqlite3 **db) {
    char sql_statemet[N];
    char *result = NULL;

    sprintf(sql_statemet, "SELECT COUNT(friend_id) FROM friends_%s WHERE friend_id like '%s'",id_for_tablename, id_for_check_value);
    int rc = sqlite3_exec(*db, sql_statemet, callback, &result, 0);
    rc += 0;
    if(strcmp(result, "0") == 0) {
        mx_strdel(&result);
        return false;
    }
    mx_strdel(&result);
    return true;
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
