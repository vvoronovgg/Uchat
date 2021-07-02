#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"


static void m_allocation_initializing(db_user_log_in_reply **log_in_reply, errors **error, sqlite3 **db); //выделяет и заполняет структуру нач. значениями
static void free_log_in_req(db_user_log_in_req **log_in_req);   //удаляет log_in_req (запрос)
static void delete_reply_from_db(db_user_log_in_reply **reply_from_db);

/*возвращает ответ log_in_reply на запрос log_in_reply*/
db_user_log_in_reply *log_in_req_to_reply(db_user_log_in_req **log_in_req, errors **error) {
    if (!*log_in_req)
        return NULL;

    db_user_log_in_reply *log_in_reply = NULL;
    sqlite3 *db = NULL;

    open_db(&db);
    m_allocation_initializing(&log_in_reply, error, &db);

    if (db == NULL) {       //в случае не успеха открытия БД
        failed_to_open_db(" in function 'log_in_req_to_reply' ", error);
        free_log_in_req(log_in_req);
        return NULL;
    }
    find_user_by_credentials_and_fill_log_in_reply(&log_in_reply, *log_in_req, &db, error);
    sqlite3_close(db);
    free_log_in_req(log_in_req);

    if ((*error)->error_message) 
        delete_reply_from_db(&log_in_reply);

    return log_in_reply;
}

/*выделяет память и инициализирует структуру начальными значениями*/
static void m_allocation_initializing(db_user_log_in_reply **log_in_reply, errors **error, sqlite3 **db) {
    *log_in_reply = (db_user_log_in_reply*)malloc(sizeof(db_user_log_in_reply));
    (*log_in_reply)->user_first_name = NULL;
    (*log_in_reply)->user_id = NULL;
    (*log_in_reply)->user_last_name = NULL;
    (*log_in_reply)->user_logged_in = NULL;
    (*log_in_reply)->user_login = NULL;
    (*log_in_reply)->user_phone_number = NULL;
    (*log_in_reply)->user_email = NULL;
    (*log_in_reply)->row = 0;
    (*log_in_reply)->error = *error;
    (*log_in_reply)->db = *db;

    for (int i = 0; i < MAX_MESS_AMNT; i++) {
        (*log_in_reply)->friends_email[i] = NULL;
        (*log_in_reply)->friends_f_name[i] = NULL;
        (*log_in_reply)->friends_l_name[i] = NULL;
        (*log_in_reply)->friends_login[i] = NULL;
        (*log_in_reply)->friends_ph_number[i] = NULL;
        (*log_in_reply)->friends_id[i] = NULL;
    }
}

/*очищает память (удаляет запрос log_in)*/
static void free_log_in_req(db_user_log_in_req **log_in_req) {
    mx_strdel(&(*log_in_req)->log_in_time);
    mx_strdel(&(*log_in_req)->user_login);
    mx_strdel(&(*log_in_req)->user_password);
    mx_strdel(&(*log_in_req)->user_phone_number);
    free(*log_in_req);
    *log_in_req = NULL;
}

/*очищает структуру, в случае ошибки*/
static void delete_reply_from_db(db_user_log_in_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->user_first_name);
    mx_strdel(&(*reply_from_db)->user_last_name);
    mx_strdel(&(*reply_from_db)->user_login);
    mx_strdel(&(*reply_from_db)->user_logged_in);
    mx_strdel(&(*reply_from_db)->user_id);
    mx_strdel(&(*reply_from_db)->user_phone_number);
    mx_strdel(&(*reply_from_db)->user_email);
    (*reply_from_db)->error = NULL;
    (*reply_from_db)->db = NULL;
    free(*reply_from_db);

    for (int i = 0; i < MAX_MESS_AMNT; i++) {
        mx_strdel(&(*reply_from_db)->friends_email[i]);
        mx_strdel(&(*reply_from_db)->friends_f_name[i]);
        mx_strdel(&(*reply_from_db)->friends_l_name[i]);
        mx_strdel(&(*reply_from_db)->friends_login[i]);
        mx_strdel(&(*reply_from_db)->friends_id[i]);
        mx_strdel(&(*reply_from_db)->friends_ph_number[i]);
    }
    *reply_from_db = NULL;
}
