#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void if_unsuccessful_exec(sqlite3 **db, int exec_try, char **err_msg, char *sql,
                                const char *was_invoked_in, errors **error);

/*такое же, что и sqlite3_exec, только void, и обрабатывает ошибки*, 
    //void *save_result  -- куда будет записываться результат (адрес на любой тип)
    //sqlite3 **db -- адрес указателя на БД
    //char *sql -- запрос SQL
    //int (*callback)(void *, int, char **, char **) -- указатель на ф-ю обратного вызова
    //errors **error -- адрес на указатель на структуру errors, место, куда будет записываться ошибка в случае неудачи
    //const char *was_invoked_in -- название функции, где был вызван sqlite3_better_exec для **error
    */ 
void sqlite3_better_exec(sqlite3 **db, char *sql, 
                        int (*callback)(void *, int, char **, char **), 
                        void *save_result, errors **error, 
                        const char *was_invoked_in) {

    if ((*error)->error_message == NULL) {
        int exec_try;
        char *err_msg = NULL;
        
        exec_try = sqlite3_exec(*db, sql, callback, save_result, &err_msg);
        if_unsuccessful_exec(db, exec_try, &err_msg, sql, was_invoked_in, error);
    }
}

static void if_unsuccessful_exec(sqlite3 **db, int exec_try, char **err_msg, char *sql,
                                const char *was_invoked_in, errors **error) {
    if (exec_try != SQLITE_OK) {
        char message[N + 100];

        sprintf(message, "%s\n\n    SQL:\n%s\n\n    in function '%s\n'", *err_msg, sql, was_invoked_in);
        failed_to_exec(message, error);
        sqlite3_free(*err_msg);
        sqlite3_close(*db);
    }
}
