#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);

/*определяет: искать по номеру телефона или логину в uchat.db
//возвращает: 
"user_phone_number" - по номеру телефона
"user_login" - по логину
*/

char *by_phone_number_or_login(char *ph_num, sqlite3 **db, errors **error, const char *was_invoked_in) {
    char sql[N];
    char *answer = NULL;

    if (ph_num == NULL)
        return (char *)"user_login";

    sql_make_simple_select_in("user_phone_number", "users", "user_phone_number", ph_num, sql, *error);
    sqlite3_better_exec(db, sql, callback, &answer, error, was_invoked_in);

    if (answer == NULL)
        return (char *)"user_login";
        
    mx_strdel(&answer);
    return (char *)"user_phone_number";
}

static void save_data( char *what, char **where);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(data[0], here);
    return 0;
}

static void save_data(char *what, char **where) {
    *where = mx_strdup(what);
}

