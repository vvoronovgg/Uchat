#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

#define GIFFT "get_info_from_friends_table"

static int callback_friends_id(void *here, int count, char **data, char **columns);

static void make_sql_get_friends_id(char sql[N], db_user_log_in_reply *log_in, errors *error);

/*достает инфу из таблицы 'friends_[user_id] и 'users' и записывает в структуру*/
void get_info_from_friends_table(db_user_log_in_reply **log_in, errors **error, sqlite3 **db) {
    if ((*error)->error_message || !log_in || !*log_in || !db || !*db)
        return;

    char sql[N];

    proverka_tablic_friends((*log_in)->user_id, db, error);
    make_sql_get_friends_id(sql, *log_in, *error);
    sqlite3_better_exec(db, sql, callback_friends_id, log_in, error, GIFFT);
}

static void make_sql_get_friends_id(char sql[N], db_user_log_in_reply *log_in, errors *error) {
    if (!log_in || error->error_message)
        return;
    
    char *limit = mx_itoa(MAX_MESS_AMNT);
    sprintf(sql, "select friend_id from (select * from friends_%s order by number desc limit %s) order by number;", log_in->user_id, limit);
    mx_strdel(&limit);
}

//----------------------------------------------CALLBACKS------------------------------------------------

static void save_data_friends_id(db_user_log_in_reply **log_in, char **data);

static int callback_friends_id(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data_friends_id(here, data);
    return 0;
}

static void make_sql_get_friends_info(char sql[N], db_user_log_in_reply *log_in, errors *error);

static int callback_friends_info(void *here, int count, char **data, char **columns);

#define SDFI "save_data_friends_id"

static void save_data_friends_id(db_user_log_in_reply **log_in, char **data) {
    if (!log_in || !*log_in ||
        !data || !*data)
        return;

    char sql[N];
    
    (*log_in)->friends_id[(*log_in)->row] = mx_strdup(data[0]);
    make_sql_get_friends_info(sql, *log_in, (*log_in)->error);
    sqlite3_better_exec(&(*log_in)->db, sql, callback_friends_info, log_in, &(*log_in)->error, SDFI);
    (*log_in)->row++;
}

static void make_sql_get_friends_info(char sql[N], db_user_log_in_reply *log_in, errors *error) {
    if (!log_in || error->error_message)
        return;
    
    char *limit = mx_itoa(MAX_MESS_AMNT);
    sprintf(sql, "select user_first_name, user_last_name, user_login, user_email, user_phone_number from users where user_id = %s limit %s;", 
            log_in->friends_id[log_in->row], limit);
    mx_strdel(&limit);
}

static void save_data_friends_info(db_user_log_in_reply **log_in, char **data);

static int callback_friends_info(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data_friends_info(here, data);
    return 0;
}

static void save_data_friends_info(db_user_log_in_reply **log_in, char **data) {
    if (!log_in || !*log_in ||
        !data || !*data)
        return;

    (*log_in)->friends_f_name[(*log_in)->row] = mx_strdup(data[0]);
    (*log_in)->friends_l_name[(*log_in)->row] = mx_strdup(data[1]);
    (*log_in)->friends_login[(*log_in)->row] = mx_strdup(data[2]);
    (*log_in)->friends_email[(*log_in)->row] = mx_strdup(data[3]);
    (*log_in)->friends_ph_number[(*log_in)->row] = mx_strdup(data[4]);
}
