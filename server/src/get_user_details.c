#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);
static void make_sql_get_udetails(char sql[N], char *u_id);

/*возвращает информацию о пользователе (при отправке сообщения)*/
void get_user_details(db_private_message_reply **pr_mess_reply, db_private_message_req *pr_mess_req,
                    errors **error, sqlite3 **db) {
    if (!pr_mess_req || !*pr_mess_reply || !pr_mess_reply ||
        !db || !*db || (*error)->error_message) {
            return;
    }
        
    char sql[N];
    make_sql_get_udetails(sql, pr_mess_req->sender_id);
    sqlite3_better_exec(db, sql, callback, pr_mess_reply, error, "get_user_details");
    
    if (!(*error)->error_message) {
        (*pr_mess_reply)->receiver_id = mx_strdup(pr_mess_req->receiver_id);
        (*pr_mess_reply)->sender_id = mx_strdup(pr_mess_req->sender_id);
    }
}

/*создание sql-запроса для БД, чтобы достать реквизиты пользователя*/
static void make_sql_get_udetails(char sql[N], char *u_id) {
    if (!sql || !u_id)
        return;

    sprintf(sql, "select user_first_name, user_last_name, user_login, user_email, user_phone_number from users where user_id like '%s'", u_id);
}

static void save_data(db_private_message_reply **pr_mess_reply, char **data);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(here, data);
    return 0;
}

static void save_data(db_private_message_reply **pr_mess_reply, char **data) {
    if (!pr_mess_reply || !*pr_mess_reply ||
        !data || !*data)
        return;

    (*pr_mess_reply)->sender_f_name = mx_strdup(data[0]);
    (*pr_mess_reply)->sender_l_name = mx_strdup(data[1]);
    (*pr_mess_reply)->sender_login = mx_strdup(data[2]);
    (*pr_mess_reply)->sender_email = mx_strdup(data[3]);
    (*pr_mess_reply)->sender_ph_number = mx_strdup(data[4]);
}
