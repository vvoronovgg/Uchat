//
// Created by Andrii Danylenko on 11/8/20.
//

#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);
static void if_unsuccessful_exec(sqlite3 **db, int exec_try, char *sql,
                                 const char *was_invoked_in, errors **error);

void check_user(db_private_message_req *private_message_req, errors **error, sqlite3 **db) {
    if ((*error)->error_message || !private_message_req || !db || !*db)
        return;
    char sql_statemet[N];
    char *query_result = NULL;
    sprintf(sql_statemet, " SELECT count(*) FROM users WHERE user_id = %s OR user_id = %s;",
            private_message_req->sender_id, private_message_req->receiver_id);
    int rc = sqlite3_exec(*db, sql_statemet, callback, &query_result, 0);
    
    if (mx_strcmp(query_result, "1") == 0 && 
        mx_strcmp(private_message_req->receiver_id, private_message_req->sender_id) == 0) {
    }
    else if (mx_strcmp(query_result, "2") != 0) {
        if_unsuccessful_exec(db, rc, sql_statemet, "check_user", error);
    }

    mx_strdel(&query_result);
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

static void if_unsuccessful_exec(sqlite3 **db, int exec_try, char *sql,
                                 const char *was_invoked_in, errors **error) {
        char message[N + 100];
        exec_try += 1;

        sprintf(message, "\n\n no a user -  SQL:\n%s\n\n    in function '%s\n'", sql, was_invoked_in);
        failed_to_exec(message, error);
        sqlite3_close(*db);
}
