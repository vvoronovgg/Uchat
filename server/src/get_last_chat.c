#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

#define GLC "get_last_chat"

static void sql_users_are_in_db(db_get_chat_with_sel_user_req *get_chat_req, char sql[N]);
static int users_callback(void *here, int count, char **data, char **columns);
static int callback_arrays(void *here, int count, char **data, char **columns);


/*возвращает последний чат между source_user и dest_user*/
void get_last_chat(db_get_chat_with_sel_user_reply **get_chat_reply, db_get_chat_with_sel_user_req *get_chat_req, 
                   sqlite3 **db, errors **error) {
    if (!get_chat_req || !*get_chat_reply 
    || !get_chat_reply || !db || !*db)
        return;
    
    char sql[N];
    char *in_db = NULL;         //динам
    char *table_name = NULL;    //динам

    sql_users_are_in_db(get_chat_req, sql);      //пользователи в БД?
    sqlite3_better_exec(db, sql, users_callback, &in_db, error, GLC);
    table_name = proverka_tablic(get_chat_req->dest_user_id, get_chat_req->source_user_id, db); //существует ли таблица chat?
    
    if (table_name && in_db && !(*error)->error_message     //если пользователь пишет сам себе, таблица чат существует
        && mx_strcmp(in_db, "1") == 0 && mx_strcmp(get_chat_req->dest_user_id, get_chat_req->source_user_id) == 0) {
            make_sql_get_last_messages(sql, table_name);
            sqlite3_better_exec(db, sql, callback_arrays, get_chat_reply, error, GLC);
    }

    else {
        if (in_db && mx_strcmp(in_db, "2") != 0) {          //если пользователи не были найдены в БД
            if (!(*error)->error_message) {
                no_users(error, GLC, get_chat_req->dest_user_id, get_chat_req->source_user_id);
            }
        }

        if (table_name && in_db && mx_strcmp(in_db, "2") == 0 && !(*error)->error_message) {    //если пользователи были найдены в БД, таблица чат существует
            make_sql_get_last_messages(sql, table_name);
            sqlite3_better_exec(db, sql, callback_arrays, get_chat_reply, error, GLC);
        }
    }

    (*get_chat_reply)->dest_user_id = mx_strdup(get_chat_req->dest_user_id);
    (*get_chat_reply)->source_user_id = mx_strdup(get_chat_req->source_user_id);
    mx_strdel(&in_db);
    mx_strdel(&table_name);
}

static void sql_users_are_in_db(db_get_chat_with_sel_user_req *get_chat_req, char sql[N]) {
   if (!get_chat_req || !sql)
        return;
   
   sprintf(sql, "SELECT count(*) FROM users WHERE user_id = %s OR user_id = %s;", 
   get_chat_req->dest_user_id, get_chat_req->source_user_id);
}

//----------------------------------------------CALLBACKS-----------------------------------------------------------

static void save_data_users(char *what, char **where);

static int users_callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data_users(data[0], here);
    return 0;
}

static void save_data_users( char *what, char **where) {
    *where = mx_strdup(what);
}

static void save_data_arrays(db_get_chat_with_sel_user_reply **chat_with, char **data);

static int callback_arrays(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data_arrays(here, data);
    return 0;
}


static void save_data_arrays(db_get_chat_with_sel_user_reply **chat_with, char **data) {
    if (!chat_with || !*chat_with ||
        !data || !*data)
        return;

    (*chat_with)->messages_senders[(*chat_with)->row] = mx_strdup(data[0]);
    (*chat_with)->last_50_messages[(*chat_with)->row] = mx_strdup(data[1]);
    (*chat_with)->dates[(*chat_with)->row] = mx_strdup(data[2]);
    (*chat_with)->row++;
}

